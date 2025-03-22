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

    static Matrix translation(Vector translation);

    static Matrix rotation(Quaternion rotation, Point p);

    static Matrix rotation(PrecisionType angle, Point p, Vector axis = Vector::Z_Axis());

    static Matrix scale(Vector factors);

    static Matrix lookAt(Point eye, Vector direction, Vector up);

    static Matrix perspective(PrecisionType near, PrecisionType far, PrecisionType aspect, PrecisionType fovTan);

    Vector getTranslation() const;

    Quaternion getRotation() const;

    Vector getRotationAxis() const;

    // TODO scale
    Vector getScale() const { return {1.f, 1.f, 1.f}; }

    static Transformation Identity() noexcept { return Transformation(Matrix::Identity()); }

    friend void from_json(const json& json, Transformation& transformation);

private:
    Matrix M;
};

Transformation operator*(const Matrix& M, const Transformation& T) noexcept;

void from_json(const json& json, Transformation& transformation);
} // Barta
