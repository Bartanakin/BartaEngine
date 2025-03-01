#pragma once
#include <Geometrics/Point.h>
#include <pch.h>

namespace Barta {

class Circle {
public:
    Circle() noexcept = default;

    Circle(PrecisionType radius, Point center);

    PrecisionType getRadius() const;

    Point getCenter() const;

    bool isWithin(Point point) const noexcept;

    PrecisionType radius;
    Point center;
};

inline std::ostream& operator<<(
    std::ostream& stream,
    const Circle& circle
) noexcept {
    return stream << "(" << circle.getCenter().toVector() << ", " << circle.getRadius() << ")";
}

Circle operator*(const Matrix& M, const Circle& circle) noexcept;

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    Circle,
    radius,
    center
)
}
