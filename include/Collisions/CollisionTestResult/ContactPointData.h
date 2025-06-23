#pragma once
#include "Geometrics/Point.h"
#include <pch.h>

namespace Barta {
struct ConvexIndexFactor {
    unsigned int index;
    PrecisionType value;
};

struct ContactPointData {
    Vector normVector;
    Point contactPoint;
    std::vector<ConvexIndexFactor> convexIndexFactors1;
    Vector displacement1;
    std::vector<ConvexIndexFactor> convexIndexFactors2;
    Vector displacement2;
};
}
