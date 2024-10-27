#pragma once
#include "../Geometrics/Vector2f.h"
#include "../pch.h"

namespace Barta {

struct DynamicsDifference {
    DynamicsDifference(
        Vector2f velocity,
        Vector2f acceleration = {},
        float rotationVelocity = 0.f
    ):
        velocity(velocity),
        acceleration(acceleration),
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

    Vector2f velocity;
    Vector2f acceleration;
    float rotationVelocity;
};
}
