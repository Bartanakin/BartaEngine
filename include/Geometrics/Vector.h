#pragma once
#include <Geometrics/Quaternion.h>
#include <pch.h>

namespace Barta {

inline void from_json(
    const json& j,
    Quaternion& q
) {
    j.at("x").get_to(q.x());
    j.at("y").get_to(q.y());
    j.at("z").get_to(q.z());
    j.at("w").get_to(q.w());
}

using VectorBase = Eigen::Vector<PrecisionType, 4>;

class Vector {
public:
    Vector() noexcept = default;
    static constexpr float ZEROING_EDGE = 0.001f;

    Vector(
        PrecisionType x,
        PrecisionType y,
        PrecisionType z = 0.f
    ):
        base{x, y, z, static_cast<PrecisionType>(0)} {}

    explicit Vector(
        const VectorBase& v
    ):
        Vector(v.x(), v.y(), v.z()) {}

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

    Vector operator-() const noexcept { return {-this->x(), -this->y(), -this->z()}; }

    Vector operator-(
        const Vector& v
    ) const noexcept {
        return {this->x() - v.x(), this->y() - v.y(), this->z() - v.z()};
    }

    Vector operator+(
        const Vector& v
    ) const noexcept {
        return {this->x() + v.x(), this->y() + v.y(), this->z() + v.z()};
    }

    PrecisionType dot(
        const Vector& v
    ) const noexcept {
        return this->base.dot(v.base);
    }

    Vector cross(
        const Vector& v
    ) const noexcept {
        return static_cast<Vector>(this->base.cross3(v.base));
    }

    PrecisionType norm() const noexcept { return this->base.norm(); }

    PrecisionType squaredNorm() const noexcept { return this->base.squaredNorm(); }

    PrecisionType squaredDistance(
        Vector v
    ) const {
        return (*this - v).squaredNorm();
    }

    Vector proj(
        const Vector v
    ) const noexcept {
        return *this * (this->dot(v) / this->norm());
    }

    Vector perp(
        const Vector v
    ) const noexcept {
        return v - this->proj(v);
    }

    std::string toString() const noexcept {
        std::stringstream ss;

        ss << "(" << this->x() << "," << this->y() << ")";

        return ss.str();
    }

    Vector operator*(
        PrecisionType scalar
    ) const {
        return {scalar * this->x(), scalar * this->y(), scalar * this->z()};
    }

    Vector operator/(
        PrecisionType scalar
    ) const {
        return *this * (1.f / scalar);
    }

    Vector operator*(
        const Matrix& M
    ) const {
        auto v = M * this->base;

        return {v.x(), v.y(), v.z()};
    }

    Vector& operator+=(
        const Vector& vector
    ) noexcept {
        *this = *this + vector;

        return *this;
    }

    Vector zeroised() const noexcept {
        auto vector = *this;
        for (PrecisionType& value: vector.base) {
            if (std::abs(value) < ZEROING_EDGE) {
                value = static_cast<PrecisionType>(0);
            }
        }

        return vector;
    }

    Vector normalised() const noexcept {
        auto vector = *this;
        auto norm = this->norm();
        for (PrecisionType& value: vector.base) {
            value /= norm;
        }

        return vector;
    }

    Matrix crossOperator() const noexcept {
        Matrix M = Matrix::Zero(4, 4);

        M(0, 1) = -this->z();
        M(0, 2) = this->y();
        M(1, 0) = this->z();
        M(1, 2) = -this->x();
        M(2, 0) = -this->y();
        M(2, 1) = this->x();

        return M;
    }

    bool operator==(const Vector& zero) const = default;

    static Vector Zero() { return {0.f, 0.f, 0.f}; }

    static Vector X_Axis() { return {1.f, 0.f, 0.f}; }

    static Vector Y_Axis() { return {0.f, 1.f, 0.f}; }

    static Vector Z_Axis() { return {0.f, 0.f, 1.f}; }

    friend Vector operator*(const Matrix& M, const Vector& v);

private:
    VectorBase base;
};

inline Vector operator*(
    PrecisionType scalar,
    const Vector& v
) noexcept {
    return v * scalar;
}

inline Vector operator*(
    const Matrix& M,
    const Vector& v
) {
    auto p2 = M * v.base;

    return {p2.x(), p2.y(), p2.z()};
}

inline void to_json(
    json& j,
    const Vector& v
) {
    j = json{
        {"x", v.x(), "y", v.y(), "z", v.z()}
    };
}

inline void from_json(
    const json& j,
    Vector& v
) {
    j.at("x").get_to(v[0]);
    j.at("y").get_to(v[1]);
    j.at("z").get_to(v[2]);
    v[3] = static_cast<PrecisionType>(0);
}

} // Barta
