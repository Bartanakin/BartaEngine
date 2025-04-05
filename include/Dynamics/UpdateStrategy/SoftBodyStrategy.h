#pragma once
#include <Dynamics/UpdateStrategy/UpdateStrategyConcept.h>
#include <Objects/Rigid/RigidObjectInterface.h>
#include <pch.h>

namespace Barta::Dynamics::UpdateStrategy {
class SoftBodyStrategy { // TODO
public:
    template<DynamicsAwareConcept ObjectType>
    void prepare(
        ObjectType& object,
        float time
    ) {
        std::cout << "TODO - prepare" << std::endl;
    }

    template<DynamicsAwareConcept ObjectType>
    void update(
        ObjectType& object,
        bool doForward
    ) {
        std::cout << "TODO - update" << std::endl;
    }
};

static_assert(UpdateStrategyConcept<SoftBodyStrategy, RigidObjectInterface>);
}
