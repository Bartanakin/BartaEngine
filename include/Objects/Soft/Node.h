#pragma once
#include <Dynamics/DynamicsDTOCollection.h>
#include <pch.h>

namespace Barta::Objects::Soft {
struct Node {
    Point restPosition;
    DynamicsDTOCollection dynamicsDTOCollection;
    unsigned int tag;
    bool isZeroDirichlet;

    Node() noexcept = default;

    Node(
        DynamicsDTOCollection dynamicsDTOCollection,
        unsigned int tag,
        bool isZeroDirichlet
    ) noexcept:
        restPosition(dynamicsDTOCollection.dynamicsDTOs[DynamicsDTOIteration::CURRENT].massCenter),
        tag(tag),
        dynamicsDTOCollection(dynamicsDTOCollection),
        isZeroDirichlet(isZeroDirichlet) {}

    Node(
        Point massCenter
    ) noexcept:
        restPosition(massCenter),
        dynamicsDTOCollection(DynamicsDTO{massCenter}),
        tag(0),
        isZeroDirichlet(false) {}
};
}
