#pragma once
#include "../pch.h"
#include "DynamicsAwareListConcept.h"
#include "DynamicsUpdateStrategyInterface.h"

#define ZEROING_EDGE 0.005f

namespace Barta {

template<DynamicsAwareListConcept DynamicsAwareList>
class ConstVelocityDynamicsUpdateStrategy: public DynamicsUpdateStrategyInterface {
public:
    ConstVelocityDynamicsUpdateStrategy(
        DynamicsAwareList& objectList
    ) noexcept:
        objectList(objectList) {}

    virtual ~ConstVelocityDynamicsUpdateStrategy() noexcept = default;

    void prepare(
        const float deltaTime
    ) override {
        for (auto object: this->objectList) {
            auto& dynamics = DynamicsAwareInterface::getCurrentDynamics(*object);
            if (dynamics.hasInfiniteMass) {
                continue;
            }

            DynamicsDTO nextDynamics = dynamics;
            nextDynamics.massCenter = dynamics.massCenter + deltaTime * nextDynamics.velocity;
            auto rotationChange = Quaternion(deltaTime * 0.5f, 0, 0, 0) * static_cast<Quaternion>(dynamics.angularVelocity) * dynamics.rotation;
            nextDynamics.rotation = {
                dynamics.rotation.w() + rotationChange.w(),
                dynamics.rotation.x() + rotationChange.x(),
                dynamics.rotation.y() + rotationChange.y(),
                dynamics.rotation.z() + rotationChange.z(),
            };

            DynamicsAwareInterface::getNextDynamics(*object) = nextDynamics;
        }
    }

    Vector applyAllowedDirections(
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

    void update(
        bool runForward = true
    ) override {
        for (auto object: this->objectList) {
            auto& dynamics = DynamicsAwareInterface::getCurrentDynamics(*object);
            auto& nextDynamics = DynamicsAwareInterface::getNextDynamics(*object);
            if (dynamics.hasInfiniteMass) {
                continue;
            }

            // TODO apply allowed directions for rotation velocity
            nextDynamics.velocity = applyAllowedDirections(nextDynamics.allowedDirections, nextDynamics.velocity).zeroised();

            auto shift = applyAllowedDirections(nextDynamics.allowedDirections, nextDynamics.massCenter - dynamics.massCenter).zeroised();
            auto additionalRotation = nextDynamics.rotation * dynamics.rotation.inverse();

            object->move(shift);
            object->rotate(additionalRotation);

            if (runForward) {
                object->getDynamicsDTOs().forward();
            }
        }
    }

private:
    DynamicsAwareList& objectList;
};

typedef ConstVelocityDynamicsUpdateStrategy<DynamicsAwareInterface::DynamicsAwareList> DefaultDynamicsUpdateStrategy;
}
