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
            auto& dynamics = object->getDynamicsDTOs()[DynamicsDTOIteration::CURRENT];
            if (dynamics.hasInfiniteMass) {
                continue;
            }

            DynamicsDTO nextDynamics = dynamics;
            auto acceleration = dynamics.force / dynamics.mass;
            nextDynamics.velocity = dynamics.velocity + acceleration * deltaTime;
            nextDynamics.massCenter = dynamics.massCenter + deltaTime * (nextDynamics.velocity + 0.5f * deltaTime * acceleration);

            object->getDynamicsDTOs()[DynamicsDTOIteration::NEXT] = nextDynamics;
        }
    }

    Vector2f applyAllowedDirections(
        const std::vector<Vector2f>& allowedDirections,
        Vector2f newVector
    ) const {
        if (newVector.zeroised() != Barta::Vector2f{}) {
            for (auto& allowedDirection: allowedDirections) {
                auto scalarProduct = allowedDirection.normalised() * newVector.normalised();
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
            auto& dynamics = object->getDynamicsDTOs()[DynamicsDTOIteration::CURRENT];
            auto& nextDynamics = object->getDynamicsDTOs()[DynamicsDTOIteration::NEXT];
            if (dynamics.hasInfiniteMass) {
                continue;
            }

            nextDynamics.velocity = applyAllowedDirections(nextDynamics.allowedDirections, nextDynamics.velocity);

            // TODO add response force handling
            nextDynamics.force = applyAllowedDirections(nextDynamics.allowedDirections, nextDynamics.force);

            object->move(applyAllowedDirections(nextDynamics.allowedDirections, nextDynamics.massCenter - dynamics.massCenter));
            // TODO
            // object->rotate(
            //     nextDynamics.rotationVelocity * object.deltaTime,
            //     dynamics.massCenter
            // );

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
