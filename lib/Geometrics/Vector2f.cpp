#include <Geometrics/Vector2f.h>
#include <pch.h>

Barta::Vector2f::Vector2f(
    const Vector2f& second
):
    x(second.x),
    y(second.y) {}

Barta::Vector2f::Vector2f(
    sf::Vector2f vector
):
    x(vector.x),
    y(vector.y) {}

Barta::Vector2f& Barta::Vector2f::operator=(const Vector2f& second) = default;

Barta::Vector2f Barta::Vector2f::operator*(
    float scalar
) const noexcept {
    return Vector2f(scalar * this->x, scalar * this->y);
}

Barta::Vector2f Barta::Vector2f::operator/(
    float scalar
) const noexcept {
    return {this->x / scalar, this->y / scalar};
}

float Barta::Vector2f::operator*(
    const Vector2f& second
) const {
    return this->getX() * second.getX() + this->getY() * second.getY();
}

Barta::Vector2f Barta::Vector2f::operator-(
    const Vector2f& second
) const {
    return Vector2f(this->x - second.x, this->y - second.y);
}

Barta::Vector2f Barta::Vector2f::operator+(
    const Vector2f& second
) const {
    return Vector2f(this->getX() + second.getX(), this->getY() + second.getY());
}

Barta::Vector2f& Barta::Vector2f::operator+=(
    const Vector2f& second
) {
    this->x += second.x;
    this->y += second.y;

    return *this;
}

bool Barta::Vector2f::operator==(
    const Vector2f& second
) const {
    return this->x == second.x && this->y == second.y;
}

float Barta::Vector2f::squareOfDistance(
    const Vector2f& second
) const {
    auto AminusB = *this - second;

    return (AminusB) * (AminusB);
}

Barta::Vector2f Barta::Vector2f::perpendicular() const {
    return Vector2f(this->getY(), -this->getX());
}

Barta::Vector2f Barta::Vector2f::normalised() const {
    return *this * (1.f / std::sqrt(this->squareOfDistance(Vector2f())));
}

float Barta::Vector2f::normSquare() const {
    return this->operator*(*this);
}

std::string Barta::Vector2f::toString() const noexcept {
    std::stringstream ss;

    ss << "(" << this->getX() << "," << this->getY() << ")";

    return ss.str();
}

float Barta::Vector2f::operator^(
    const Vector2f second
) const noexcept {
    return this->x * second.y - this->y * second.x;
}

Barta::Vector2f Barta::Vector2f::rotated(
    float radians
) const noexcept {
    const float sin = std::sin(radians);
    const float cos = std::cos(radians);

    return {Vector2f(cos, -sin) * *this, Vector2f(sin, cos) * *this};
}

float Barta::Vector2f::angleTo(
    const Vector2f second
) const noexcept {
    return std::atan2(second.y, second.x) - std::atan2(this->y, this->x);
}

Barta::Vector2f Barta::Vector2f::projection(
    const Vector2f v
) const noexcept {
    return this->operator*(this->operator*(v) / this->normSquare());
}

Barta::Vector2f Barta::Vector2f::zeroised(const float edge) const noexcept {
    auto vector = *this;
    if (std::abs(vector.x) < edge) {
        vector.x = 0.f;
    }

    if (std::abs(vector.y) < edge) {
        vector.y = 0.f;
    }

    return vector;
}

Barta::Vector2f Barta::Vector2f::zeroise(
    Vector2f vector,
    float edge
) noexcept {
    if (std::abs(vector.x) < edge) {
        vector.x = 0.f;
    }

    if (std::abs(vector.y) < edge) {
        vector.y = 0.f;
    }

    return vector;
}

std::ostream& Barta::operator<<(
    std::ostream& s,
    const Vector2f& v
) {
    return s << v.toString();
}

Barta::Vector2f Barta::operator*(
    float scalar,
    const Vector2f& vector
) noexcept {
    return vector * scalar;
}
