#pragma once
#include <pch.h>

namespace Barta {

using PrecisionType = float;
using Matrix = Eigen::Matrix<PrecisionType, 4, 4>;

class Quaternion: public Eigen::Quaternion<PrecisionType> {
public:
    Quaternion() = default;

    Quaternion(
        PrecisionType w,
        PrecisionType x,
        PrecisionType y,
        PrecisionType z
    ) noexcept:
        Eigen::Quaternion<PrecisionType>(w, x, y, z) {}

    Quaternion(
        const Eigen::Quaternion<PrecisionType>& base
    ) noexcept:
        Eigen::Quaternion<PrecisionType>(base) {}
};

inline void from_json(
    const nlohmann::json& j,
    Quaternion& q
) {
    PrecisionType angle = j.at("angle");
    Eigen::Vector3<PrecisionType> n;
    n.x() = j.at("x");
    n.y() = j.at("y");
    n.z() = j.at("z");
    n.normalize();
    n *= std::sin(angle / 2.);

    q.w() = std::cos(angle / 2.);
    q.x() = n.x();
    q.y() = n.y();
    q.z() = n.z();
}
}
