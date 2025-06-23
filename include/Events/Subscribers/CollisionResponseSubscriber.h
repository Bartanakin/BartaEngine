#pragma once
#include "Events/Events/CollisionEvent.h"
#include <Events/BartaEventLoggerInterface.h>
#include <Utilities/DynamicsIteration.h>

namespace Barta {

template<typename CollisionEventType>
class CollisionResponseSubscriber: public EventSubscriber<CollisionEventType> {
public:
    static constexpr float COEFFICIENT_OF_RESTITUTION = 1.f;

    CollisionResponseSubscriber() = default;

    ~CollisionResponseSubscriber() noexcept = default;

    bool handle(
        CollisionEventType& event
    ) override {
        auto& testResult = event.getTestResult().collisionTestResult;
        auto firstObject = event.getTestResult().object1;
        auto secondObject = event.getTestResult().object2;
        if (firstObject->isToBeDeleted() || secondObject->isToBeDeleted()) {
            return true;
        }

        if (testResult.staticCollision) {
            return true;
        }

        const auto& firstDynamics = Utils::extractCurrentDynamics(*firstObject);
        const auto& secondDynamics = Utils::extractCurrentDynamics(*secondObject);

        float massInverted = 0.f;
        if (!firstDynamics.hasInfiniteMass) {
            massInverted += firstDynamics.inverseMass;
        }

        if (!secondDynamics.hasInfiniteMass) {
            massInverted += secondDynamics.inverseMass;
        }

        // TODO calculate real velocity from integration
        auto j = -(1.f + COEFFICIENT_OF_RESTITUTION) * (firstDynamics.velocity - secondDynamics.velocity).dot(testResult.normVector)
                 / (testResult.normVector.dot(testResult.normVector) * massInverted);
        this->calculateNewVelocity(-j, firstObject, testResult.normVector);
        this->calculateNewVelocity(j, secondObject, testResult.normVector);

        return true;
    }

    bool isToBeDeleted() const noexcept override { return false; }

private:
    template<typename ObjectType> // TODO add concepts
    void calculateNewVelocity(
        float j,
        ObjectType* dynamicsObject,
        Vector normVector
    ) const noexcept {
        const auto& oldDynamics = Utils::extractCurrentDynamics(*dynamicsObject);
        if (oldDynamics.hasInfiniteMass) {
            return;
        }

        Utils::extractNextDynamics(*dynamicsObject).velocity += normVector * (j * oldDynamics.inverseMass);
    }
};

template<typename T1, typename T2>
using StaticCollisionResponseSubscriberType = CollisionResponseSubscriber<CollisionEvent<T1, T2>>;

}
