#include <Dynamics/SoftBody/StVenantKirchhoffDynamics.h>
#include "Utilities/MatrixUtilities.h"

namespace Barta::Dynamics::SoftBody {

// constexpr PrecisionType MU = 5300.f;
// constexpr PrecisionType LAMBDA = 99500.f;

constexpr PrecisionType MU = 100.f;
constexpr PrecisionType LAMBDA = 1000.f;
// constexpr PrecisionType MU = 10.f;
// constexpr PrecisionType LAMBDA = 100.f;

using Utils::Matrix3Type;
using Utils::Matrix9Type;

StiffnessMatrixType StVenantKirchhoffDynamics::assembleTangentStiffnessMatrix(
    const Objects::Soft::Mesh& mesh,
    const NodalVectorType& nodesPositions
) {
    StiffnessMatrixType tangentStiffnessMatrix = StiffnessMatrixType::Zero(nodesPositions.size(), nodesPositions.size());
    for (const auto& e: mesh.elements) {
        Matrix3Type D_e_star_inv = e.getInverseReferenceShapeMatrix();
        Matrix3Type D_e = e.calculateShapeMatrix(mesh.nodes, nodesPositions);
        Matrix3Type F_e = D_e * D_e_star_inv;
        Matrix9Type H9 = Matrix9Type::Zero();
        for (int j = 0; j < 9; j++) {
            Matrix3Type delta_D_e = Matrix3Type::Zero();
            delta_D_e(j % 3, j / 3) = 1.;
            Matrix3Type delta_F_e = delta_D_e * D_e_star_inv;

            Matrix3Type term1 = MU * delta_F_e * (F_e.transpose() * F_e - 0.5 * Matrix3Type::Identity());
            Matrix3Type term2 = MU * F_e * delta_F_e.transpose() * F_e;
            Matrix3Type term3 = MU * (F_e * F_e.transpose() - 0.5 * Matrix3Type::Identity()) * delta_F_e;
            Matrix3Type term4 = 0.5 * LAMBDA * (F_e.transpose() * F_e - Matrix3Type::Identity()).trace() * delta_F_e;
            Matrix3Type term5 = LAMBDA * (F_e.transpose() * delta_F_e).trace() * F_e;

            Matrix3Type dP = -(term1 + term2 + term3 + term4 + term5) * D_e_star_inv.transpose() / (6. * std::abs(D_e_star_inv.determinant()));
            for (int i = 0; i < 9; i++) {
                H9(i, j) = dP(i % 3, i / 3);
            }
        }

        SoftBodyDynamicsInterface::emplace12Matrix(
            Utils::create12MatrixFrom9MatrixAndThirdNewtonLaw(H9),
            e.getNodeIndices(),
            tangentStiffnessMatrix,
            mesh.nodes.size() - mesh.dirichletNodeCount
        );
    }

    return tangentStiffnessMatrix;
}

NodalVectorType StVenantKirchhoffDynamics::calculateNodalForces(
    const Objects::Soft::Mesh& mesh,
    const NodalVectorType& nodesPositions
) {
    NodalVectorType forces = NodalVectorType::Zero(nodesPositions.size());
    for (const auto& e: mesh.elements) {
        Matrix3Type D_e_star_inv = e.getInverseReferenceShapeMatrix();
        Matrix3Type D_e_star_inv_T = D_e_star_inv.transpose();
        Matrix3Type F_e = e.calculateShapeMatrix(mesh.nodes, nodesPositions) * D_e_star_inv;
        Matrix3Type E_e = 0.5 * (F_e.transpose() * F_e - Matrix3Type::Identity());
        Matrix3Type P_e = F_e * (2. * MU * E_e + LAMBDA * E_e.trace() * Matrix3Type::Identity());
        Matrix3Type H = -(P_e * D_e_star_inv_T) / (6. * std::abs(D_e_star_inv.determinant()));
        const auto& nodeIndices = e.getNodeIndices();
        Eigen::Vector3<PrecisionType> force4 = Eigen::Vector3<PrecisionType>::Zero();
        for (int i = 0; i < 3; ++i) {
            force4 += H.block<3, 1>(0, i);
            if (3 * nodeIndices[i] >= nodesPositions.size()) {
                continue;
            }

            forces.block<3, 1>(3 * nodeIndices[i], 0) += H.block<3, 1>(0, i);
        }

        if (3 * nodeIndices[3] >= nodesPositions.size()) {
            continue;
        }

        forces.block<3, 1>(3 * nodeIndices[3], 0) -= force4;
    }

    return forces;
}
}
