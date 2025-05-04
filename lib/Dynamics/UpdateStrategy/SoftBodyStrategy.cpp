#include <Dynamics/UpdateStrategy/SoftBodyStrategy.h>
#include "Dynamics/Mass/ConstantPointMassDistributionCalculator.h"
#include "Dynamics/UpdateStrategy/ExplicitEulerStrategy.h"

namespace Barta::Dynamics::UpdateStrategy {

constexpr unsigned int MAX_ITERATIONS = 1000;

SoftBodyStrategy::SoftBodyStrategy(
    std::unique_ptr<SoftBody::SoftBodyDynamicsInterface> softBodyDynamics,
    std::unique_ptr<Mass::MassDistributionCalculatorInterface> massCalculator
) noexcept:
    softBodyDynamics(std::move(softBodyDynamics)),
    massCalculator(std::move(massCalculator)) {}

template<>
void Barta::Dynamics::UpdateStrategy::SoftBodyStrategy::prepare<Barta::Objects::Soft::SoftObject>(
    Objects::Soft::SoftObject& object,
    float time
) {
    auto& mesh = object.getMesh();
    const auto NODAL_VECTOR_SIZE = mesh.getNodalVectorSize();
    SoftBody::NodalVectorType initialPositions = SoftBody::NodalVectorType::Zero(NODAL_VECTOR_SIZE);
    SoftBody::NodalVectorType initialVelocities = SoftBody::NodalVectorType::Zero(NODAL_VECTOR_SIZE);
    unsigned int i = 0;
    for (const auto& node: mesh.nodes) {
        if (node.isZeroDirichlet) {
            break;
        }

        const auto& dynamicsData = node.dynamicsDTOCollection.dynamicsDTOs[DynamicsDTOIteration::CURRENT];

        initialPositions[3 * i] = dynamicsData.massCenter.x();
        initialPositions[3 * i + 1] = dynamicsData.massCenter.y();
        initialPositions[3 * i + 2] = dynamicsData.massCenter.z();

        initialVelocities[3 * i] = dynamicsData.velocity.x();
        initialVelocities[3 * i + 1] = dynamicsData.velocity.y();
        initialVelocities[3 * i + 2] = dynamicsData.velocity.z();

        ++i;
    }

    SoftBody::NodalVectorType positions = initialPositions;
    SoftBody::StiffnessMatrixType massMatrixInverse = this->massCalculator->assembleInverseMassMatrix(mesh, positions);
    auto iterCounter = 0;
    while (true) {
        ++iterCounter;
        if (iterCounter >= MAX_ITERATIONS) {
            throw std::runtime_error("Iteration count exceeded");
        }

        SoftBody::StiffnessMatrixType A = -time * massMatrixInverse * this->softBodyDynamics->assembleTangentStiffnessMatrix(mesh, positions)
                                          + SoftBody::StiffnessMatrixType::Identity(NODAL_VECTOR_SIZE, NODAL_VECTOR_SIZE) / time;
        SoftBody::NodalVectorType b = initialVelocities + (initialPositions - positions) / time
                                      + time * massMatrixInverse * this->softBodyDynamics->calculateNodalForces(mesh, positions);
        SoftBody::NodalVectorType delta_positions = A.colPivHouseholderQr().solve(b);

        bool precisionReached = true;
        float maxEr = 0.f;
        for (const auto& u_i: delta_positions) {
            if (std::abs(u_i) > maxEr) {
                maxEr = std::abs(u_i);
            }

            if (std::abs(u_i) > 1e-4) {
                precisionReached = false;
            }
        }

        positions += delta_positions;
        if (precisionReached) {
            break;
        }
    }

    SoftBody::NodalVectorType velocities = (positions - initialPositions) / time;

    ExplicitEulerStrategy().prepare(object, time);
    i = 0;
    for (auto& node: mesh.nodes) {
        if (node.isZeroDirichlet) {
            continue;
        }

        auto& dynamicsData = node.dynamicsDTOCollection.dynamicsDTOs[DynamicsDTOIteration::NEXT];

        dynamicsData.massCenter.x() = positions[3 * i];
        dynamicsData.massCenter.y() = positions[3 * i + 1];
        dynamicsData.massCenter.z() = positions[3 * i + 2];

        dynamicsData.velocity.x() = velocities[3 * i];
        dynamicsData.velocity.y() = velocities[3 * i + 1];
        dynamicsData.velocity.z() = velocities[3 * i + 2];
        dynamicsData.velocity = dynamicsData.velocity.zeroised();

        ++i;
    }

    this->massCalculator->prepareMassDistribution(object);
}

template<>
void Barta::Dynamics::UpdateStrategy::SoftBodyStrategy::update<Barta::Objects::Soft::SoftObject>(
    Objects::Soft::SoftObject& object,
    bool doForward
) {
    ExplicitEulerStrategy().update(object, doForward);
    if (!doForward) {
        return;
    }

    for (auto& node: object.getMesh().nodes) {
        node.dynamicsDTOCollection.forward();
    }
}

}
