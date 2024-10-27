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
        Vector2f massCenter = {}
    ):
        velocity(velocity),
        hasInfiniteMass(hasInfiniteMass),
        mass(mass),
        force(force),
        rotationVelocity(rotationVelocity),
        massCenter(massCenter) {}

    DynamicsDTO& operator=(
        const DynamicsDTO& second
    ) {
        this->velocity = second.velocity;
        this->hasInfiniteMass = second.hasInfiniteMass;
        this->mass = second.mass;
        this->force = second.force;
        this->rotationVelocity = second.rotationVelocity;
        this->massCenter = second.massCenter;

        return *this;
    }

    DynamicsDTO(
        const DynamicsDTO& second
    ):
        velocity(second.velocity),
        hasInfiniteMass(second.hasInfiniteMass),
        mass(second.mass),
        force(second.force),
        rotationVelocity(second.rotationVelocity),
        massCenter(second.massCenter) {}

    DynamicsDifference getDynamicsDifference(
        const DynamicsDTO& second
    ) const {
        return {
            this->velocity - second.velocity,
            this->force * (1.f / this->mass) - second.force * (1.f / second.mass),
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
            -this->massCenter // TODO
        };
    }

    Vector2f velocity;
    bool hasInfiniteMass;
    float mass;
    Vector2f force;
    float rotationVelocity;
    Vector2f massCenter;
};
}
