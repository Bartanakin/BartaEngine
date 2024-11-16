#pragma once
#include "BartaShapes/AABB.h"
#include "BartaShapes/Circle.h"
#include "Ray.h"
#include "Segment.h"

namespace Barta {
namespace Intersections {

    float lineAndLineRespectToFirst(const Segment& I1, const Segment& I2) noexcept;

    std::vector<std::tuple<float, float>> segmentAndSegment(const Segment& I1, const Segment& I2) noexcept;

    std::vector<std::tuple<float, float>> segmentAndAABB(const Segment& I, const AABB& aabb);

    std::vector<float> rayAndCircle(const Ray& ray, const Circle& c) noexcept;

    std::vector<float> segmentAndCircle(const Segment& I, const Circle& c) noexcept;
}
}
