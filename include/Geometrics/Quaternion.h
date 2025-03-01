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
}
