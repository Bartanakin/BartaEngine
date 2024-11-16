//
// Created by bartanakin on 10/22/24.
//

#pragma once
#include "DynamicsDTO.h"
#include "DynamicsDTOCollection.h"
#include "pch.h"

template<typename T>
concept DynamicsAwareConcept = requires(T t, Barta::Vector2f v, float rotation) {
    { t.getDynamicsDTOs() } -> std::same_as<Barta::DynamicsDTOCollection&>;
    { t.getCurrentDynamicsData() } -> std::same_as<const Barta::DynamicsDTO&>;
    { t.getNextDynamicsData() } -> std::same_as<Barta::DynamicsDTO&>;
    { t.isToBeDeleted() } -> std::same_as<bool>;
    { t.move(v) } -> std::same_as<void>;
    { t.rotate(rotation, v) } -> std::same_as<void>;
};

template<typename T>
concept DynamicsAwareListConcept = requires(T t) {
    { t.begin() } -> std::forward_iterator;
    { t.end() } -> std::sentinel_for<decltype(t.begin())>;

    // TODO add concept for list entry
};
