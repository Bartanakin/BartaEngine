#pragma once
#include "CollisionResponseSubscriber.h"
#include "Dynamics/Mass/MassDistributionCalculatorInterface.h"
#include "Dynamics/SoftBody/SoftBodyDynamicsInterface.h"
#include "Objects/CollisionSubscribers/RigidObjectSoftObjectCollisionSubscriber.h"
#include <pch.h>

namespace Barta {

template<>
class CollisionResponseSubscriber<Events::RigidObjectSoftObject>:
    public EventSubscriber<CollisionEvent<RigidObjectInterface, Objects::Soft::SoftObject>> {
public:
    explicit CollisionResponseSubscriber(
        Dynamics::SoftBody::SoftBodyDynamicsInterface& softBodyDynamics,
        Dynamics::Mass::MassDistributionCalculatorInterface& massCalculator,
        TimerInterface& timer
    ) noexcept:
        softBodyDynamics(softBodyDynamics),
        massCalculator(massCalculator),
        timer(timer) {}

    bool handle(
        CollisionEvent<RigidObjectInterface, Objects::Soft::SoftObject>& event
    ) override {
        auto& testResult = event.getTestResult().collisionTestResult;
        auto firstObject = event.getTestResult().object1;
        auto secondObject = event.getTestResult().object2;
        if (firstObject->isToBeDeleted() || secondObject->isToBeDeleted()) {
            return true;
        }

        const auto m = testResult.contactPointDataArray.size();
        auto& mesh = secondObject->getMesh();
        const auto NODAL_VECTOR_SIZE = mesh.getNodalVectorSize();
        const auto EXTENDED_NODAL_VECTOR_SIZE = NODAL_VECTOR_SIZE + 3;

        Matrix softBodyTransform = secondObject->getDynamicsDTOs()[DynamicsDTOIteration::CURRENT].getTransformation().getMatrix();
        Matrix softBodyTransformInv = softBodyTransform.inverse();
        auto extendedCurrentPositions = this->createExtendedVector(
            mesh.collectPositions(CURRENT),
            (softBodyTransformInv * firstObject->getDynamicsDTOs()[CURRENT].massCenter).toVector(),
            EXTENDED_NODAL_VECTOR_SIZE
        );
        auto extendedCurrentVelocities = this->createExtendedVector(
            mesh.collectVelocities(CURRENT),
            softBodyTransformInv * firstObject->getDynamicsDTOs()[CURRENT].velocity,
            EXTENDED_NODAL_VECTOR_SIZE
        );

        softBodyTransformInv = secondObject->getDynamicsDTOs()[DynamicsDTOIteration::NEXT].getTransformation().getMatrix().inverse();
        auto nextPositions = mesh.collectPositions(NEXT);
        auto extendedNextPositions = this->createExtendedVector(
            nextPositions,
            (softBodyTransformInv * firstObject->getDynamicsDTOs()[NEXT].massCenter).toVector(),
            EXTENDED_NODAL_VECTOR_SIZE
        );

        auto nodalForces_hat =
            this->createExtendedVector(this->softBodyDynamics.calculateNodalForces(mesh, nextPositions), {0, 0, 0}, EXTENDED_NODAL_VECTOR_SIZE);

        Eigen::MatrixX<PrecisionType> K_hat = Eigen::MatrixX<PrecisionType>::Zero(EXTENDED_NODAL_VECTOR_SIZE, EXTENDED_NODAL_VECTOR_SIZE);
        K_hat.block(0, 0, NODAL_VECTOR_SIZE, NODAL_VECTOR_SIZE) = -this->softBodyDynamics.assembleTangentStiffnessMatrix(mesh, nextPositions);

        Eigen::MatrixX<PrecisionType> M_hat = Eigen::MatrixX<PrecisionType>::Zero(EXTENDED_NODAL_VECTOR_SIZE, EXTENDED_NODAL_VECTOR_SIZE);
        M_hat.block(0, 0, NODAL_VECTOR_SIZE, NODAL_VECTOR_SIZE) = this->massCalculator.assembleMassMatrix(mesh, nextPositions);
        M_hat(EXTENDED_NODAL_VECTOR_SIZE - 3, EXTENDED_NODAL_VECTOR_SIZE - 3) = 1. / firstObject->getDynamicsDTOs()[CURRENT].inverseMass;
        M_hat(EXTENDED_NODAL_VECTOR_SIZE - 2, EXTENDED_NODAL_VECTOR_SIZE - 2) = 1. / firstObject->getDynamicsDTOs()[CURRENT].inverseMass;
        M_hat(EXTENDED_NODAL_VECTOR_SIZE - 1, EXTENDED_NODAL_VECTOR_SIZE - 1) = 1. / firstObject->getDynamicsDTOs()[CURRENT].inverseMass;

        auto deltaT = this->timer.getCurrentDeltaTime();

        struct ObjectiveDataPass {
            Eigen::MatrixX<PrecisionType> Q;
            Eigen::VectorX<PrecisionType> c;
        };

        ObjectiveDataPass dataPass;
        dataPass.Q = -1. / (deltaT * deltaT) * M_hat - K_hat;
        dataPass.c = -dataPass.Q * extendedNextPositions
                     + 1. / deltaT * M_hat * ((extendedNextPositions - extendedCurrentPositions) / deltaT - extendedCurrentVelocities)
                     - nodalForces_hat;

        // std::cout << "Q" << std::endl << dataPass.Q << std::endl;
        // std::cout << "c" << std::endl << dataPass.c << std::endl;
        nlopt::opt opt(nlopt::LD_MMA, EXTENDED_NODAL_VECTOR_SIZE);
        opt.set_max_objective(
            [](const std::vector<double>& x, std::vector<double>& grad, void* data) {
                auto* castData = static_cast<ObjectiveDataPass*>(data);
                Eigen::VectorX<PrecisionType> ex = Eigen::Map<const Eigen::VectorX<PrecisionType>>(x.data(), x.size());
                if (!grad.empty()) {
                    Eigen::VectorX<PrecisionType> eigenGrad = -castData->Q * ex - castData->c;

                    std::copy(eigenGrad.data(), eigenGrad.data() + eigenGrad.size(), grad.begin());
                }

                // auto xd = 0.5 * ex.dot(castData->Q * ex) + castData->c.dot(ex);
                // std::cout << "f " << xd << std::endl;
                return 0.5 * ex.dot(castData->Q * ex) + castData->c.dot(ex);
            },
            &dataPass
        );

        struct ConstraintDataPass {
            Eigen::VectorX<PrecisionType> eta_j;
            double b;
        };

        /// debug
        Eigen::MatrixX<PrecisionType> eta = Eigen::MatrixX<PrecisionType>::Zero(m, EXTENDED_NODAL_VECTOR_SIZE);
        Eigen::VectorX<PrecisionType> b = Eigen::VectorX<PrecisionType>::Zero(m);
        //

        std::vector<ConstraintDataPass> constraintDataPasses(m);
        for (unsigned int j = 0; j < m; j++) {
            constraintDataPasses[j].b = -testResult.contactPointDataArray[j].convexIndexFactors1[0].value
                                        * testResult.contactPointDataArray[j].normVector.dot(testResult.contactPointDataArray[j].displacement1);
            constraintDataPasses[j].eta_j = this->calculateMappingOperatorRow(testResult.contactPointDataArray[j], EXTENDED_NODAL_VECTOR_SIZE);

            // debug
            b[j] = constraintDataPasses[j].b;
            eta.block(j, 0, 1, EXTENDED_NODAL_VECTOR_SIZE) = constraintDataPasses[j].eta_j.transpose();
            //

            opt.add_inequality_constraint(
                [](const std::vector<double>& x, std::vector<double>& grad, void* data) {
                    auto* castData = static_cast<ConstraintDataPass*>(data);
                    Eigen::VectorX<PrecisionType> ex = Eigen::Map<const Eigen::VectorX<PrecisionType>>(x.data(), x.size());
                    if (!grad.empty()) {
                        Eigen::VectorX<PrecisionType> eigenGrad = -castData->eta_j;

                        std::copy(eigenGrad.data(), eigenGrad.data() + eigenGrad.size(), grad.begin());
                    }

                    // auto xd = -castData->eta_j.dot(ex) + castData->r;
                    // std::cout << "c " << xd << std::endl;

                    return -castData->eta_j.dot(ex) + castData->b;
                },
                constraintDataPasses.data() + j,
                1e-4
            );
        }

        opt.set_xtol_abs(1e-2);
        // std::cout << "eta" << std::endl << eta << std::endl;
        // std::cout << "b" << std::endl << b << std::endl;
        std::vector<double> minimizedVector(EXTENDED_NODAL_VECTOR_SIZE);
        std::copy(extendedNextPositions.data(), extendedNextPositions.data() + extendedNextPositions.size(), minimizedVector.begin());
        double minf;
        // std::cout << extendedCurrentPositions << std::endl;
        auto result = opt.optimize(minimizedVector, minf);
        Eigen::VectorX<PrecisionType> extendedConstrainedPositions(EXTENDED_NODAL_VECTOR_SIZE);
        std::copy(minimizedVector.data(), minimizedVector.data() + minimizedVector.size(), extendedConstrainedPositions.begin());

        Eigen::VectorX<PrecisionType> extendedConstrainedVelocities = (extendedConstrainedPositions - extendedCurrentPositions) / deltaT;

        mesh.updateNextDynamics(extendedConstrainedPositions, extendedConstrainedVelocities);

        this->massCalculator.prepareMassDistribution(*secondObject);

        firstObject->getDynamicsDTOs()[NEXT].massCenter = softBodyTransform * Point{
            extendedConstrainedPositions[EXTENDED_NODAL_VECTOR_SIZE - 3],
            extendedConstrainedPositions[EXTENDED_NODAL_VECTOR_SIZE - 2],
            extendedConstrainedPositions[EXTENDED_NODAL_VECTOR_SIZE - 1]
        };
        firstObject->getDynamicsDTOs()[NEXT].velocity = softBodyTransform * Vector{
            extendedConstrainedVelocities[EXTENDED_NODAL_VECTOR_SIZE - 3],
            extendedConstrainedVelocities[EXTENDED_NODAL_VECTOR_SIZE - 2],
            extendedConstrainedVelocities[EXTENDED_NODAL_VECTOR_SIZE - 1]
        };

        // law of energy conservation
        PrecisionType currEnergy = 0., nextEnergy = 0.;
        for (unsigned int j = 0; j < mesh.nodes.size(); j++) {
            currEnergy += mesh.nodes[j].dynamicsDTOCollection[CURRENT].velocity.squaredNorm() / mesh.nodes[j].dynamicsDTOCollection[CURRENT].inverseMass;
            nextEnergy += mesh.nodes[j].dynamicsDTOCollection[NEXT].velocity.squaredNorm() / mesh.nodes[j].dynamicsDTOCollection[NEXT].inverseMass;
        }

        currEnergy += (softBodyTransformInv * firstObject->getDynamicsDTOs()[CURRENT]).velocity.squaredNorm() / firstObject->getDynamicsDTOs()[CURRENT].inverseMass;
        nextEnergy += (softBodyTransformInv * firstObject->getDynamicsDTOs()[NEXT].velocity).squaredNorm() / firstObject->getDynamicsDTOs()[NEXT].inverseMass;

        auto lambda = std::sqrt(currEnergy/nextEnergy);
        for (unsigned int j = 0; j < mesh.nodes.size(); j++) {
            mesh.nodes[j].dynamicsDTOCollection[NEXT].velocity *= lambda;
        }

        firstObject->getDynamicsDTOs()[NEXT].velocity *= lambda;

        return true;
    }

    Eigen::VectorX<PrecisionType> calculateMappingOperatorRow(
        const ContactPointData& contactPointData,
        unsigned int extendedNodalVectorSize
    ) const {
        Eigen::VectorX<PrecisionType> eta_j = Eigen::VectorX<PrecisionType>::Zero(extendedNodalVectorSize);
        for (unsigned int i = 0; i < contactPointData.convexIndexFactors2.size(); i++) {
            auto convexPair = contactPointData.convexIndexFactors2[i];
            if (convexPair.index >= extendedNodalVectorSize) { // Dirichlet node
                continue;
            }

            eta_j[3 * convexPair.index + 0] = -convexPair.value * contactPointData.normVector.x();
            eta_j[3 * convexPair.index + 1] = -convexPair.value * contactPointData.normVector.y();
            eta_j[3 * convexPair.index + 2] = -convexPair.value * contactPointData.normVector.z();
        }

        eta_j[extendedNodalVectorSize - 3] = contactPointData.normVector.x();
        eta_j[extendedNodalVectorSize - 2] = contactPointData.normVector.y();
        eta_j[extendedNodalVectorSize - 1] = contactPointData.normVector.z();

        return eta_j;
    }

    bool isToBeDeleted() const noexcept override { return false; }

private:
    Dynamics::SoftBody::SoftBodyDynamicsInterface& softBodyDynamics;
    Dynamics::Mass::MassDistributionCalculatorInterface& massCalculator;
    TimerInterface& timer;

    Eigen::VectorX<PrecisionType> createExtendedVector(
        const Eigen::VectorX<PrecisionType>& base,
        const Vector& addon,
        const unsigned int EXTENDED_NODAL_VECTOR_SIZE
    ) const {
        Eigen::VectorX<PrecisionType> ret(EXTENDED_NODAL_VECTOR_SIZE);
        ret.block(0, 0, EXTENDED_NODAL_VECTOR_SIZE - 3, 1) = base;
        ret[EXTENDED_NODAL_VECTOR_SIZE - 3] = addon.x();
        ret[EXTENDED_NODAL_VECTOR_SIZE - 2] = addon.y();
        ret[EXTENDED_NODAL_VECTOR_SIZE - 1] = addon.z();

        return ret;
    }
};

using RigidSoftCollisionResponseSubscriber = CollisionResponseSubscriber<CollisionEvent<RigidObjectInterface, Objects::Soft::SoftObject>>;
}
