#pragma once
#include "../pch.h"

namespace Barta {

class Vector2f {
public:
    static constexpr float ZEROING_EDGE = 0.005f;
    float x;
    float y;
    constexpr Vector2f() noexcept = default;

    constexpr Vector2f(
        float x,
        float y
    ):
        x(x),
        y(y) {}

    Vector2f(const Vector2f& second);
    Vector2f(sf::Vector2f vector);
    Vector2f& operator=(const Vector2f&);

    float getX() const { return this->x; }

    float getY() const { return this->y; }

    Vector2f operator*(float scalar) const noexcept;

    Vector2f operator/(float scalar) const noexcept;

    float operator*(const Vector2f&) const;

    constexpr Vector2f operator-() const { return Vector2f(-this->x, -this->y); }

    Vector2f operator-(const Vector2f&) const;

    Vector2f operator+(const Vector2f&) const;

    Vector2f& operator+=(const Vector2f&);

    bool operator==(const Vector2f&) const;

    float squareOfDistance(const Vector2f&) const;

    Vector2f perpendicular() const;

    Vector2f normalised() const;

    float normSquare() const;

    std::string toString() const noexcept;

    float operator^(Vector2f) const noexcept;

    Vector2f rotated(float radians) const noexcept;

    float angleTo(Vector2f) const noexcept;

    Vector2f projection(Vector2f) const noexcept;

    Vector2f zeroised(float = ZEROING_EDGE) const noexcept;

    /**
     * @deprecated
     */
    static Vector2f zeroise(Vector2f vector, float edge) noexcept;

    friend Vector2f operator*(float, const Vector2f&) noexcept;
};

Vector2f operator*(float, const Vector2f&) noexcept;

std::ostream& operator<<(std::ostream&, const Vector2f&);
}
