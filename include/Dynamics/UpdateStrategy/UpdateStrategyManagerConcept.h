#pragma once
#include <Dynamics/UpdateStrategy/DynamicsAwareConcept.h>
#include <ListManagerConcept.h>
#include <pch.h>

namespace Barta::Dynamics::UpdateStrategy {

// clang-format off
template<typename UpdateStrategyManager, typename ObjectList, typename ObjectType>
concept UpdateStrategyManagerConcept = ListManagerConcept<ObjectList, ObjectType>
    && DynamicsAwareConcept<ObjectType>
    && requires(
        ObjectList& objectList,
        UpdateStrategyManager updateStrategyManager,
        float time,
        bool doUpdate
    ) {
        { updateStrategyManager.prepare(objectList, time) } -> std::same_as<void>;
        { updateStrategyManager.update(objectList, doUpdate) } -> std::same_as<void>;
    };
// clang-format on

}
