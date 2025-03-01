#pragma once
#include <Geometrics/Point.h>

namespace Barta {

class Transformation {
public:
    Transformation() = default;

    explicit Transformation(
        const Matrix& M
    ):
        M(M) {}

    const Matrix& getMatrix() const { return this->M; }

    static Matrix translation(
        Vector translation
    ) {
        Matrix M = Matrix::Identity();
        M(0, 3) = translation.x();
        M(1, 3) = translation.y();
        M(2, 3) = translation.z();

        return M;
    }

    static Matrix rotation(
        Quaternion rotation,
        Point p
    ) {
        rotation = rotation.normalized();
        auto angle = 2.f * std::acos(rotation.w());
        Vector axis = {rotation.x(), rotation.y(), rotation.z()};
        axis = 1.f / std::sin(angle / 2.f) * axis;

        return Transformation::rotation(angle, p, axis);
    }

    static Matrix rotation(
        PrecisionType angle,
        Point p,
        Vector axis = Vector::Z_Axis()
    ) {
        Matrix R = Matrix::Identity(4, 4);
        auto sin = std::sin(angle);
        auto cos = std::cos(angle);
        auto x = axis[0];
        auto y = axis[1];
        auto z = axis[2];

        R(0, 0) = cos + (1 - cos) * x * x;
        R(0, 1) = (1 - cos) * x * y - sin * z;
        R(0, 2) = (1 - cos) * x * z + sin * y;

        R(1, 0) = (1 - cos) * x * y + sin * z;
        R(1, 1) = cos + (1 - cos) * y * y;
        R(2, 1) = (1 - cos) * y * z - sin * x;

        R(2, 0) = (1 - cos) * x * z - sin * y;
        R(2, 1) = (1 - cos) * y * z + sin * x;
        R(2, 2) = cos + (1 - cos) * z * z;

        R = Transformation::translation(p.toVector()) * R * Transformation::translation(-p.toVector());

        return R;
    }

    Vector getTranslation() const { return {this->M(0, 3), this->M(1, 3), this->M(2, 3)}; }

    Quaternion getRotation() const {
        Vector axis = {
            M(2, 1) - M(1, 2),
            M(0, 2) - M(2, 0),
            M(1, 0) - M(0, 1),
        };
        if (axis.zeroised() == Vector::Zero()) {
            axis = Vector::Z_Axis();
        }

        axis = axis.normalised();
        auto cos = (this->M.trace() - 2.f) / 2.f;
        if (cos >= 1.f) {
            cos = 1.f;
        } else if (cos <= -1.f) {
            cos = -1.f;
        }

        auto sin = -(axis.crossOperator() * this->M).trace() / 2.f;
        if (sin >= 1.f) {
            sin = 1.f;
        } else if (sin <= -1.f) {
            sin = -1.f;
        }

        return Quaternion(std::atan2(sin, cos), axis.x(), axis.y(), axis.z());
    }

    Vector getRotationAxis() const {
        if (this->M.isIdentity(0.00001f)) {
            return Vector::Z_Axis();
        }

        return {
            M(2, 1) - M(1, 2),
            M(0, 2) - M(2, 0),
            M(1, 0) - M(0, 1),
        };
    }

    // TODO scale
    Vector getScale() const { return {1.f, 1.f, 1.f}; }

    static Transformation Identity() noexcept { return Transformation(Matrix::Identity()); }

    friend inline void from_json(const json& json, Transformation& transformation);

private:
    Matrix M;
};

inline Transformation operator*(
    const Matrix& M,
    const Transformation& T
) noexcept {
    return Transformation(M.operator*(T.getMatrix()));
}

inline void from_json(
    const json& json,
    Transformation& transformation
) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::string key = "a" + std::to_string(i + 1) + std::to_string(j + 1);
            if (json.contains(key)) {
                json.at(key).get_to(transformation.M(i, j));
            } else {
                transformation.M(i, j) = (i == j) ? 1. : 0.;
            }
        }
    }
}
} // Barta
