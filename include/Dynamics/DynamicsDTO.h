#pragma once
#include <Geometrics/Point.h>
#include <Geometrics/Transformation.h>

namespace Barta {

struct DynamicsDTO {
    DynamicsDTO(
        // movement
        const Point& massCenter = Point::Zero(),
        const Vector& velocity = Vector::Zero(),
        const PrecisionType& inverseMass = 1.f,
        // rotation
        const Quaternion& rotation = {1., 0., 0., 0.},
        const Vector& angularVelocity = Vector::Zero(),
        const Matrix& inverseInertia = Matrix::Identity(),
        // others
        const std::vector<Vector>& allowedDirections = {}
    ):
        massCenter(std::move(massCenter)),
        velocity(std::move(velocity)),
        hasInfiniteMass(std::move(false)),
        inverseMass(std::move(inverseMass)),
        rotation(std::move(rotation)),
        angularVelocity(std::move(angularVelocity)),
        hasInfiniteInertia(std::move(false)),
        inverseInertia(std::move(inverseInertia)),
        allowedDirections(std::move(allowedDirections)) {}

    // movement
    Point massCenter;
    Vector velocity;
    bool hasInfiniteMass;
    PrecisionType inverseMass;
    // rotation
    Quaternion rotation;
    Vector angularVelocity;
    bool hasInfiniteInertia;
    Matrix inverseInertia;
    // others
    std::vector<Vector> allowedDirections;

    Transformation getTransformation() const {
        return Transformation::translation(this->massCenter.toVector()) * Transformation::rotation(this->rotation) * Transformation::Identity();
    }
};

inline void from_json(
    const json& j,
    DynamicsDTO& d
) {
    d = DynamicsDTO();
    if (j.contains("massCenter")) {
        d.massCenter = j.at("massCenter");
    }

    if (j.contains("velocity")) {
        d.velocity = j.at("velocity");
    }

    if (j.contains("inverseMass")) {
        d.inverseMass = j.at("inverseMass");
    }

    if (j.contains("hasInfiniteMass")) {
        d.hasInfiniteMass = j.at("hasInfiniteMass");
    }

    if (j.contains("rotation")) {
        Quaternion rotation;
        from_json(j.at("rotation"), rotation);
        d.rotation = rotation;
    }

    if (j.contains("angularVelocity")) {
        d.angularVelocity = j.at("angularVelocity");
    }

    if (j.contains("inverseInertia")) {
        d.inverseInertia = static_cast<Transformation>(j.at("inverseInertia")).getMatrix();
    }

    if (j.contains("hasInfiniteInertia")) {
        d.hasInfiniteInertia = j.at("hasInfiniteInertia");
    }

    if (j.contains("allowedDirections")) {
        d.allowedDirections = j.at("allowedDirections");
    }
}

inline DynamicsDTO operator*(
    const Matrix& matrix,
    const DynamicsDTO& dynamics
) {
    return {
        matrix * dynamics.massCenter,
        matrix * dynamics.velocity,
        dynamics.inverseMass,
        dynamics.rotation, // TODO define the transformation
        matrix * dynamics.angularVelocity,
        dynamics.inverseInertia,
        dynamics.allowedDirections
    };
}

}
