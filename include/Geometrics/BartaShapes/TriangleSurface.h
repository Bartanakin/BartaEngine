#pragma once
#include "Geometrics/Intersections.h"
#include "Geometrics/Ray.h"
#include "Triangle.h"

namespace Barta::Geometrics::BartaShapes {
struct TriangleSurface {
    std::vector<Triangle> triangles;
    std::vector<std::array<unsigned int,3>> indices;

    TriangleSurface(std::vector<Triangle> triangles, std::vector<std::array<unsigned int,3>> indices) noexcept;

    std::vector<float> intersectsWithRay(const Ray& ray) const;

    bool isWithin(const Point& position) const;
};

}
