#pragma once
#include <Geometrics/Point.h>

namespace Barta {

class Triangle {
public:
    Triangle(Point p1, Point p2, Point p3);

    bool isWithin(Point point) const noexcept;

    const Point p1;
    const Point p2;
    const Point p3;
};

inline std::ostream& operator<<(
    std::ostream& stream,
    const Triangle& triangle
) noexcept {
    return stream << "(" << triangle.p1.toVector() << ", " << triangle.p2.toVector() << ", " << triangle.p2.toVector() << ")";
}
}
