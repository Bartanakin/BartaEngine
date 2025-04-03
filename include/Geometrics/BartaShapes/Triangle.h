#pragma once
#include <Geometrics/Point.h>

namespace Barta {

struct Triangle {
    Triangle() = default;
    Triangle(Point p1, Point p2, Point p3);

    bool isWithin(Point point) const noexcept;

    Vector getNormal() const noexcept;

    Point p1;
    Point p2;
    Point p3;
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
