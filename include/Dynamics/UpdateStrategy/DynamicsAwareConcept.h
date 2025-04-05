#pragma once
#include <Dynamics/DynamicsDTOCollection.h>
#include <Geometrics/Vector.h>
#include <ListManagerConcept.h>
#include <pch.h>

namespace Barta::Dynamics::UpdateStrategy {
// clang-format off
template<typename T>
concept DynamicsAwareConcept =
    DeleteSettable<T> && requires(
        T dynamicsAware,
        const Vector& vector,
        const Quaternion& quaternion,
        DynamicsDTOCollection& dynamicsDTOCollection,
        DynamicsDTOIteration dynamicsDTOIteration
    ) {
        { dynamicsAware.move(vector) } -> std::same_as<void>;
        { dynamicsAware.rotate(quaternion) } -> std::same_as<void>;
        { dynamicsAware.getDynamicsDTOs() } -> std::same_as<DynamicsDTOCollection&>;
        // position iteration and velocity iteration for different integration schemes
        { dynamicsAware.getForce(dynamicsDTOIteration, dynamicsDTOIteration) } -> std::same_as<Vector>;
    };

}
