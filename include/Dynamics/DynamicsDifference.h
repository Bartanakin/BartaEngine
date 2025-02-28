#pragma once
#include <Geometrics/Vector.h>
#include <pch.h>

namespace Barta {

struct DynamicsDifference {
    DynamicsDifference(
        Vector velocity,
        Vector acceleration = {},
        PrecisionType rotationVelocity = 0.f
    ):
        velocity(std::move(velocity)),
        acceleration(std::move(acceleration)),
        rotationVelocity(rotationVelocity) {}

    DynamicsDifference& operator=(
        const DynamicsDifference& second
    ) {
        this->velocity = second.velocity;
        this->rotationVelocity = second.rotationVelocity;

        return *this;
    }

    DynamicsDifference(const DynamicsDifference& second) = default;

    DynamicsDifference operator-() const { return {-this->velocity, -this->acceleration, this->rotationVelocity}; }

    Vector velocity;
    Vector acceleration;
    PrecisionType rotationVelocity;
};

inline DynamicsDifference operator*(
    const Matrix& M,
    const DynamicsDifference& dynamicsDifference
) noexcept {
    return {
        M * dynamicsDifference.velocity,
        M * dynamicsDifference.acceleration,
        dynamicsDifference.rotationVelocity // TODO - rotation speed
    };
}
}
