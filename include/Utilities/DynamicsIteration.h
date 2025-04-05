#pragma once
#include <Dynamics/UpdateStrategy/DynamicsAwareConcept.h>
#include <pch.h>

namespace Barta::Utils {

template<Dynamics::UpdateStrategy::DynamicsAwareConcept DynamicsAware>
static DynamicsDTO& extractCurrentDynamics(
    DynamicsAware& obj
) {
    return obj.getDynamicsDTOs()[Barta::DynamicsDTOIteration::CURRENT];
}

template<Dynamics::UpdateStrategy::DynamicsAwareConcept DynamicsAware>
static DynamicsDTO& extractNextDynamics(
    DynamicsAware& obj
) {
    return obj.getDynamicsDTOs()[Barta::DynamicsDTOIteration::NEXT];
}
}
