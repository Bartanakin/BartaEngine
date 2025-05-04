#pragma once
#include "Dynamics/Mass/MassDistributionCalculatorInterface.h"
#include "Dynamics/SoftBody/SoftBodyDynamicsInterface.h"
#include "Objects/Soft/SoftObject.h"
#include <Dynamics/UpdateStrategy/UpdateStrategyConcept.h>
#include <Objects/Rigid/RigidObjectInterface.h>
#include <pch.h>

namespace Barta::Dynamics::UpdateStrategy {
class SoftBodyStrategy { // TODO
public:
    explicit SoftBodyStrategy(
        std::unique_ptr<SoftBody::SoftBodyDynamicsInterface> softBodyDynamics,
        std::unique_ptr<Mass::MassDistributionCalculatorInterface> massCalculator
    ) noexcept;

    template<DynamicsAwareConcept ObjectType>
    void prepare(
        ObjectType& object,
        float time
    ) {
        throw std::runtime_error("This method is for Soft Bodies only. Define you specialization in order to use it.");
    }

    template<DynamicsAwareConcept ObjectType>
    void update(
        ObjectType& object,
        bool doForward
    ) {
        throw std::runtime_error("This method is for Soft Bodies only. Define you specialization in order to use it.");
    }

private:
    std::unique_ptr<SoftBody::SoftBodyDynamicsInterface> softBodyDynamics;
    std::unique_ptr<Mass::MassDistributionCalculatorInterface> massCalculator;
};

static_assert(UpdateStrategyConcept<SoftBodyStrategy, RigidObjectInterface>);
}

template<>
void Barta::Dynamics::UpdateStrategy::SoftBodyStrategy::prepare<Barta::Objects::Soft::SoftObject>(Objects::Soft::SoftObject& object, float time);

template<>
void Barta::Dynamics::UpdateStrategy::SoftBodyStrategy::update<Barta::Objects::Soft::SoftObject>(Objects::Soft::SoftObject& object, bool doForward);
