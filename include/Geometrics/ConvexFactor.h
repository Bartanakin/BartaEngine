//
// Created by bartanakin on 2/16/25.
//

#pragma once

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
};

}
