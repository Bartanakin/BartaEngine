#include <Geometrics/BartaShapes/TriangleSurface.h>

namespace Barta::Geometrics::BartaShapes {
TriangleSurface::TriangleSurface(
    std::vector<Triangle> triangles,
    std::vector<std::array<unsigned int, 3>> indices
) noexcept:
    triangles(std::move(triangles)),
    indices(std::move(indices)) {}

std::vector<float> TriangleSurface::intersectsWithRay(
    const Ray& ray
) const {
    std::vector<float> intersections;
    for (const auto& triangle: this->triangles) {
        auto localIntersections = Intersections::rayAndTriangle(ray, triangle);
        for (const auto& intersection: localIntersections) {
            if (intersection >= 0.) {
                intersections.push_back(intersection);
            }
        }
    }

    return intersections;
}

bool TriangleSurface::isWithin(
    const Point& position
) const {
    return this->intersectsWithRay({position, this->triangles[0].getCenter() - position}).size() % 2 != 0;
}
}
