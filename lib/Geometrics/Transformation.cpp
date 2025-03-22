#include <Geometrics/Transformation.h>

namespace Barta {

Matrix Transformation::translation(
    Vector translation
) {
    Matrix M = Matrix::Identity();
    M(0, 3) = translation.x();
    M(1, 3) = translation.y();
    M(2, 3) = translation.z();

    return M;
}

Matrix Transformation::rotation(
    Quaternion rotation,
    Point p
) {
    rotation = rotation.normalized();
    auto angle = 2.f * std::acos(rotation.w());
    Vector axis = {rotation.x(), rotation.y(), rotation.z()};
    axis = 1.f / std::sin(angle / 2.f) * axis;

    return Transformation::rotation(angle, p, axis);
}

Matrix Transformation::rotation(
    PrecisionType angle,
    Point p,
    Vector axis
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

Matrix Transformation::scale(
    Vector factors
) {
    Matrix M = Matrix::Identity();
    M(0, 0) = factors.x();
    M(1, 1) = factors.y();
    M(2, 2) = factors.z();

    return M;
}

Vector Transformation::getTranslation() const {
    return {this->M(0, 3), this->M(1, 3), this->M(2, 3)};
}

Quaternion Transformation::getRotation() const {
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

Vector Transformation::getRotationAxis() const {
    if (this->M.isIdentity(0.00001f)) {
        return Vector::Z_Axis();
    }

    return {
        M(2, 1) - M(1, 2),
        M(0, 2) - M(2, 0),
        M(1, 0) - M(0, 1),
    };
}

Matrix Transformation::lookAt(
    Point eye,
    Vector direction,
    Vector up
) {
    auto normal = up.cross(direction);
    if (normal.squaredNorm() == 0.f) {
        throw std::runtime_error("Direction cannot be parallel to the up vector");
    }

    normal = normal.normalised();
    direction = direction.normalised();
    up = -normal.cross(direction);

    Matrix R = Matrix::Zero();
    R(0, 0) = normal.x();
    R(1, 0) = normal.y();
    R(2, 0) = normal.z();

    R(0, 1) = up.x();
    R(1, 1) = up.y();
    R(2, 1) = up.z();

    R(0, 2) = -direction.x();
    R(1, 2) = -direction.y();
    R(2, 2) = -direction.z();

    R(3, 3) = static_cast<PrecisionType>(1);

    return R.transpose() * Transformation::translation(-eye.toVector());
}

Matrix Transformation::perspective(
    PrecisionType near,
    PrecisionType far,
    PrecisionType aspect,
    PrecisionType fovTan
) {
    Matrix R = Matrix::Zero();
    R(0, 0) = 1.f / fovTan;
    R(1, 1) = aspect / fovTan;
    R(2, 2) = (near + far) / (near - far);
    R(2, 3) = 2.f * (near * far) / (near - far);
    R(3, 2) = -1.f;

    return R;
}

Transformation operator*(
    const Matrix& M,
    const Transformation& T
) noexcept {
    return Transformation(M.operator*(T.getMatrix()));
}

void from_json(
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

}
