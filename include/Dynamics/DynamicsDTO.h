#pragma once
#include "DynamicsDifference.h"

namespace Barta {

struct DynamicsDTO {
    DynamicsDTO(
        Vector2f velocity,
        bool hasInfiniteMass = true,
        float mass = 0.f,
        Vector2f force = {},
        float rotationVelocity = 0.f,
        Vector2f massCenter = {},
        std::vector<Vector2f> allowedDirections = {}
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
        Vector2f acceleration{};
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

    Vector2f velocity;
    bool hasInfiniteMass;
    float mass;
    Vector2f force;
    float rotationVelocity;
    Vector2f massCenter;
    std::vector<Vector2f> allowedDirections;
};
}
