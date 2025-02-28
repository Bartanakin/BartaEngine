#pragma once
#include <Geometrics/Point.h>

namespace Barta {

class Circle {
public:
    Circle(PrecisionType radius, Point center);

    PrecisionType getRadius() const;

    Point getCenter() const;

    bool isWithin(Point point) const noexcept;

    const float radius;
    const Point center;
};

inline std::ostream& operator<<(
    std::ostream& stream,
    const Circle& circle
) noexcept {
    return stream << "(" << circle.getCenter().toVector() << ", " << circle.getRadius() << ")";
}

Circle operator*(const Matrix& M, const Circle& circle) noexcept;
}
