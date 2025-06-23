#pragma once
#include "Geometrics/Quaternion.h"
#include "Objects/Soft/Mesh.h"
#include "Objects/Soft/TetrahedralElement.h"
#include "Utilities/MatrixUtilities.h"
#include <pch.h>

namespace Barta::Dynamics::SoftBody {

using StiffnessMatrixType = Objects::Soft::StiffnessMatrixType;
using NodalVectorType = Objects::Soft::NodalVectorType;

class SoftBodyDynamicsInterface {
public:
    SoftBodyDynamicsInterface() = default;
    virtual ~SoftBodyDynamicsInterface() = default;

    virtual StiffnessMatrixType assembleTangentStiffnessMatrix(const Objects::Soft::Mesh& elements, const NodalVectorType& nodesPositions) = 0;

    virtual NodalVectorType calculateNodalForces(const Objects::Soft::Mesh& elements, const NodalVectorType& nodesPositions) = 0;

    static void emplace12Matrix(
        const Utils::Matrix12Type& m12,
        const std::array<unsigned int, 4>& nodeIndices,
        StiffnessMatrixType& stiffnessMatrix,
        unsigned int block3x3Count
    );
};
}
