#pragma once
#include "DynamicsDifference.h"
#include <Geometrics/Point.h>

namespace Barta {

struct DynamicsDTO {
    DynamicsDTO(
        Vector velocity = Vector::Zero(),
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

inline void from_json(
    const json& j,
    DynamicsDTO& d
) {
    d = DynamicsDTO();
    if (j.contains("velocity")) {
        d.velocity = j.at("velocity");
    }

    if (j.contains("hasInfiniteMass")) {
        d.hasInfiniteMass = j.at("hasInfiniteMass");
    }

    if (j.contains("mass")) {
        d.mass = j.at("mass");
    }

    if (j.contains("force")) {
        d.force = j.at("force");
    }

    if (j.contains("rotationVelocity")) {
        d.rotationVelocity = j.at("rotationVelocity");
    }

    if (j.contains("massCenter")) {
        d.massCenter = j.at("massCenter");
    }

    if (j.contains("allowedDirections")) {
        d.allowedDirections = j.at("allowedDirections");
    }
}

}
