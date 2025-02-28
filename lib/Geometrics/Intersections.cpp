//
// Created by bartanakin on 11/15/24.
//

#include <Geometrics/Intersections.h>
#include <Utilities/QuadraticEquation.h>

float Barta::Intersections::lineAndLineRespectToFirst(
    const Segment& I1,
    const Segment& I2
) noexcept {
    auto perpendicular = (I2.getEnd() - I2.getBeginning()).cross(Vector::Z_Axis());
    auto denom = perpendicular.dot(I1.getEnd() - I1.getBeginning());
    if (denom == 0.f) {
        return std::numeric_limits<float>::infinity();
    }

    return perpendicular.dot(I2.getBeginning() - I1.getBeginning()) / denom;
}

std::vector<std::tuple<float, float>> Barta::Intersections::segmentAndAABB(
    const Segment& I,
    const AABB& aabb
) {
    decltype(segmentAndSegment(I, I)) intersections;
    for (const auto& side: aabb.getSides()) {
        auto sideIntersections = segmentAndSegment(I, side);
        intersections.insert(intersections.end(), sideIntersections.begin(), sideIntersections.end());
    }

    if (intersections.size() == 2) {
        if (std::get<0>(intersections[0]) > std::get<0>(intersections[1])) {
            auto temp = intersections[0];
            intersections[0] = intersections[1];
            intersections[1] = temp;
        }
    }

    if (intersections.size() > 2) {
        throw std::runtime_error("size too long");
    }

    return intersections;
}

std::vector<std::tuple<float, float>> Barta::Intersections::segmentAndSegment(
    const Segment& I1,
    const Segment& I2
) noexcept {
    std::vector<std::tuple<float, float>> result;
    auto barCoords = std::tuple<float, float>(lineAndLineRespectToFirst(I1, I2), lineAndLineRespectToFirst(I2, I1));

    if (0.f <= std::get<0>(barCoords) && std::get<0>(barCoords) <= 1.f && 0.f <= std::get<1>(barCoords) && std::get<1>(barCoords) <= 1.f) {
        result.push_back(barCoords);
    }

    return result;
}

std::vector<float> Barta::Intersections::segmentAndCircle(
    const Segment& I,
    const Circle& c
) noexcept {
    auto sol = Intersections::rayAndCircle({I.getBeginning(), I.getEnd() - I.getBeginning()}, c);

    sol.erase(std::remove_if(sol.begin(), sol.end(), [](float t) { return 1.f < t; }), sol.end());

    return sol;
}

std::vector<float> Barta::Intersections::rayAndCircle(
    const Ray& ray,
    const Circle& c
) noexcept {
    auto d = ray.direction;
    auto m = ray.origin - c.getCenter();
    auto eq = Utils::QuadraticEquation(d.squaredNorm(), 2.f * m.dot(d), m.squaredNorm() - c.getRadius() * c.getRadius());
    eq.solve();
    auto sol = eq.getSolutions();

    sol.erase(std::remove_if(sol.begin(), sol.end(), [](float t) { return t < 0.f; }), sol.end());

    return sol;
}
