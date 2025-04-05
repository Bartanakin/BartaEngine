#pragma once
#include <Dynamics/UpdateStrategy/UpdateStrategyConcept.h>
#include <Objects/Rigid/RigidObjectInterface.h>
#include <Utilities/DynamicsIteration.h>
#include <pch.h>

namespace Barta::Dynamics::UpdateStrategy {
class ExplicitEulerStrategy {
public:
    template<DynamicsAwareConcept ObjectType>
    void prepare(
        ObjectType& object,
        float timeChange
    ) {
        auto& dynamics = Utils::extractCurrentDynamics(object);
        if (dynamics.hasInfiniteMass) {
            return;
        }

        DynamicsDTO nextDynamics = dynamics;
        nextDynamics.massCenter = dynamics.massCenter + timeChange * nextDynamics.velocity;
        nextDynamics.velocity = dynamics.velocity + timeChange * object.getForce(DynamicsDTOIteration::CURRENT, DynamicsDTOIteration::CURRENT);
        auto rotationChange = Quaternion(timeChange * 0.5f, 0, 0, 0) * static_cast<Quaternion>(dynamics.angularVelocity) * dynamics.rotation;
        nextDynamics.rotation = {
            dynamics.rotation.w() + rotationChange.w(),
            dynamics.rotation.x() + rotationChange.x(),
            dynamics.rotation.y() + rotationChange.y(),
            dynamics.rotation.z() + rotationChange.z(),
        };

        // TODO rotation dynamics

        Utils::extractNextDynamics(object) = nextDynamics;
    }

    Vector applyAllowedDirections(
        // TODO extract to a different service
        const std::vector<Vector>& allowedDirections,
        Vector newVector
    ) const {
        if (newVector.zeroised() != Vector::Zero()) {
            for (auto& allowedDirection: allowedDirections) {
                auto scalarProduct = allowedDirection.normalised().dot(newVector.normalised());
                if (scalarProduct > 0.f || std::abs(scalarProduct) < 0.00005f) {
                    continue;
                }

                if (scalarProduct < 0.f) {
                    newVector = allowedDirection.perp(newVector);
                }
            }
        }

        return newVector;
    }

    template<DynamicsAwareConcept ObjectType>
    void update(
        ObjectType& object,
        bool doUpdate
    ) {
        auto& dynamics = Utils::extractCurrentDynamics(object);
        auto& nextDynamics = Utils::extractNextDynamics(object);
        if (dynamics.hasInfiniteMass) {
            return;
        }

        // TODO apply allowed directions for rotation velocity
        nextDynamics.velocity = this->applyAllowedDirections(nextDynamics.allowedDirections, nextDynamics.velocity).zeroised();

        auto shift = applyAllowedDirections(nextDynamics.allowedDirections, nextDynamics.massCenter - dynamics.massCenter).zeroised();
        auto additionalRotation = nextDynamics.rotation * dynamics.rotation.inverse();

        object.move(shift);
        object.rotate(additionalRotation);

        if (doUpdate) {
            object.getDynamicsDTOs().forward();
        }
    }
};

static_assert(UpdateStrategyConcept<ExplicitEulerStrategy, RigidObjectInterface>);
}
