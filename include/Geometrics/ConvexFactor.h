#pragma once

#include "Utilities/Concepts/ContainerConcepts.h"
#include <Geometrics/Point.h>
#include <pch.h>

namespace Barta {

struct ConvexFactor {
    PrecisionType factor;
    Point p;

    ConvexFactor(
        PrecisionType f,
        Point p
    ):
        factor{f},
        p{std::move(p)} {}

    static Point convexCombination(
        const std::vector<ConvexFactor>& data
    ) {
        Point p = Point::Zero();
        for (const auto& factor: data) {
            p += factor.factor * factor.p.toVector();
        }

        return p;
    }

    template<typename Container>
        requires Utilities::Concepts::ConstIteratorContainerConcept<Container, Point> static Point baricentricCombination(
        const Container& data
    ) {
        auto factor = static_cast<PrecisionType>(1) / static_cast<PrecisionType>(data.size());
        Point p = Point::Zero();
        for (const auto& item: data) {
            p += factor * item.toVector();
        }

        return p;
    }
};

}
