//
// Created by bartanakin on 2/12/25.
//

#pragma once
#include <Geometrics/Vector.h>
#include <pch.h>

namespace Barta {
using EigenBaseVector = Eigen::Vector<PrecisionType, 4>;

class Point {
private:
    VectorBase base;

public:
    Point() noexcept = default;

    Point(
        PrecisionType x,
        PrecisionType y,
        PrecisionType z
    ):
        base(x, y, z, static_cast<PrecisionType>(1)) {}

    PrecisionType x() const noexcept { return this->base.x(); }

    PrecisionType y() const noexcept { return this->base.y(); }

    PrecisionType z() const noexcept { return this->base.z(); }

    PrecisionType& operator[](
        int i
    ) noexcept {
        return this->base[i];
    }

    PrecisionType operator[](
        int i
    ) const noexcept {
        return this->base[i];
    }

    Vector toVector() const { return {this->x(), this->y(), this->z()}; }

    size_t size() const noexcept { return 3; }

    explicit operator Vector() { return {this->operator[](0), this->operator[](1), this->operator[](2)}; }

    Point operator*(
        PrecisionType scalar
    ) const {
        return {scalar * this->operator[](0), scalar * this->operator[](1), scalar * this->operator[](2)};
    }

    float squaredDistance(
        Point p
    ) const {
        return (*this - p).squaredNorm();
    }

    Point& operator*=(
        PrecisionType scalar
    ) {
        this->operator[](0) *= scalar;
        this->operator[](1) *= scalar;
        this->operator[](2) *= scalar;

        return *this;
    }

    Vector operator-(
        const Point& p
    ) const {
        return {this->x() - p.x(), this->y() - p.y(), this->z() - p.z()};
    }

    Point operator-(
        const Vector& v
    ) const {
        return {this->x() - v.x(), this->y() - v.y(), this->z() - v.z()};
    }

    Point operator-() const { return {-this->x(), -this->y(), -this->z()}; }

    static Point Zero() noexcept { return {0, 0, 0}; }

    friend Point operator*(const Matrix& M, const Point& p);
};

inline std::ostream& operator<<(
    std::ostream& s,
    const Vector& v
) {
    return s << v.toString();
}

inline Point operator+(
    const Point& p,
    const Vector& v
) {
    return {p[0] + v[0], p[1] + v[1], p[2] + v[2]};
}

inline Point& operator+=(
    Point& p,
    const Vector& v
) {
    p = p + v;

    return p;
}

inline Point operator+(
    const Vector& v,
    const Point& p
) {
    return p + v;
}

inline Point operator*(
    PrecisionType scalar,
    const Point& p
) {
    return p * scalar;
}

inline Point operator*(
    const Matrix& M,
    const Point& p
) {
    auto p2 = M * p.base;

    return {p2.x(), p2.y(), p2.z()};
}

} // Barta
