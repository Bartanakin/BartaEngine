#pragma once
#include "DynamicsDifference.h"
#include <Geometrics/Point.h>

namespace Barta {

struct DynamicsDTO {
    DynamicsDTO(
        Vector velocity,
        bool hasInfiniteMass = true,
        PrecisionType mass = 0.f,
        Vector force = Vector::Zero(),
        PrecisionType rotationVelocity = 0.f,
        Point massCenter = Point::Zero(),
        std::vector<Vector> allowedDirections = {}
    ):
        velocity(velocity),
        hasInfiniteMass(hasInfiniteMass),
        mass(mass),
        force(force),
        rotationVelocity(rotationVelocity),
        massCenter(massCenter),
        allowedDirections(std::move(allowedDirections)) {}

    DynamicsDTO& operator=(const DynamicsDTO& second) = default;

    DynamicsDTO(const DynamicsDTO& second) = default;

    ~DynamicsDTO() = default;

    DynamicsDifference getDynamicsDifference(
        const DynamicsDTO& second
    ) const {
        auto acceleration = Vector::Zero();
        if (!this->hasInfiniteMass) {
            acceleration += this->force * (1.f / this->mass);
        }

        if (!second.hasInfiniteMass) {
            acceleration += -second.force * (1.f / second.mass);
        }

        return {
            this->velocity - second.velocity,
            acceleration,
            this->rotationVelocity - second.rotationVelocity,
        };
    }

    DynamicsDTO operator-() const {
        return {
            -this->velocity,
            this->hasInfiniteMass,
            -this->mass,
            -this->force,
            this->rotationVelocity,
            -this->massCenter,
            this->allowedDirections
        };
    }

    Vector velocity;
    bool hasInfiniteMass;
    PrecisionType mass;
    Vector force;
    PrecisionType rotationVelocity;
    Point massCenter;
    std::vector<Vector> allowedDirections;
};
}
