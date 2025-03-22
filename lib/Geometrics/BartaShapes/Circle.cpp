#include <Geometrics/BartaShapes/Circle.h>

namespace Barta {
Circle::Circle(
    PrecisionType radius,
    Point center
):
    radius(radius),
    center(std::move(center)) {}

PrecisionType Circle::getRadius() const {
    return this->radius;
}

Point Circle::getCenter() const {
    return this->center;
}

bool Circle::isWithin(
    Point point
) const noexcept {
    return pow(this->radius, 2) >= pow(this->center.x() - point.x(), 2) + pow(this->center.y() - point.y(), 2);
}

Circle operator*(
    const Matrix& M,
    const Circle& circle
) noexcept {
    // TODO scale
    return {
        circle.radius,
        M * circle.center,
    };
}
}
