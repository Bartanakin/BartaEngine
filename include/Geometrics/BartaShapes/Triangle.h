#pragma once
#include <Geometrics/Point.h>

namespace Barta {

struct Triangle {
    Triangle() noexcept = default;
    Triangle(Point p1, Point p2, Point p3) noexcept;

    bool isWithin(Point point) const noexcept;

    Vector getNormal() const noexcept;

    Point getCenter() const;

    Point operator[](unsigned int index) const noexcept;

    Point closestPoint(Point point) const noexcept;

    std::array<PrecisionType, 3> getConvexCoordinates(Point X) const noexcept;

    Point p1;
    Point p2;
    Point p3;

    private:
    bool belongsToUij(Point P, unsigned int i, unsigned int j) const;
};

inline std::ostream& operator<<(
    std::ostream& stream,
    const Triangle& triangle
) noexcept {
    return stream << "(" << triangle.p1.toVector() << ", " << triangle.p2.toVector() << ", " << triangle.p2.toVector() << ")";
}

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    Triangle,
    p1,
    p2,
    p3
)
}
