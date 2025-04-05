#pragma once
#include <Dynamics/UpdateStrategy/DynamicsAwareConcept.h>
#include <pch.h>

namespace Barta::Dynamics::UpdateStrategy {

template<typename UpdateStrategy, typename ObjectType>
concept UpdateStrategyConcept =
    DynamicsAwareConcept<ObjectType> && requires(ObjectType& object, UpdateStrategy updateStrategy, float time, bool doUpdate) {
        { updateStrategy.prepare(object, time) } -> std::same_as<void>;
        { updateStrategy.update(object, doUpdate) } -> std::same_as<void>;
    };

}
