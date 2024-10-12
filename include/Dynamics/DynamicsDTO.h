#pragma once
#include "../Geometrics/Vector2f.h"
#include "../pch.h"

namespace Barta {

struct DynamicsDTO {
    inline DynamicsDTO(
        Vector2f velocity,
        bool hasInfiniteMass = true,
        float mass = 0.f,
        Vector2f acceleration = {},
        float rotationVelocity = 0.f,
        Vector2f massCenter = {}
    ):
        velocity(velocity),
        hasInfiniteMass(hasInfiniteMass),
        mass(mass),
        acceleration(acceleration),
        rotationVelocity(rotationVelocity),
        massCenter(massCenter) {}

    inline DynamicsDTO& operator=(
        const DynamicsDTO& second
    ) {
        this->velocity = second.velocity;
        this->hasInfiniteMass = second.hasInfiniteMass;
        this->mass = second.mass;
        this->acceleration = second.acceleration;
        this->rotationVelocity = second.rotationVelocity;
        this->massCenter = second.massCenter;

        return *this;
    }

    inline DynamicsDTO(
        const DynamicsDTO& second
    ):
        velocity(second.velocity),
        hasInfiniteMass(second.hasInfiniteMass),
        mass(second.mass),
        acceleration(second.acceleration),
        rotationVelocity(second.rotationVelocity),
        massCenter(second.massCenter) {}

    inline DynamicsDTO getRelativeDynamics(
        const DynamicsDTO& second
    ) const {
        return {
            this->velocity - second.velocity,
            false,
            this->mass - second.mass,
            this->acceleration - second.acceleration,
            this->rotationVelocity - second.rotationVelocity,
            this->massCenter - this->massCenter // TODO
        };
    }

    inline DynamicsDTO operator-() const {
        return {
            -this->velocity,
            this->hasInfiniteMass,
            -this->mass,
            -this->acceleration,
            this->rotationVelocity,
            -this->massCenter // TODO
        };
    }

    Vector2f velocity;
    bool hasInfiniteMass;
    float mass;
    Vector2f acceleration;
    float rotationVelocity;
    Vector2f massCenter;
};
}
