#pragma once
#include "../BartaEventLoggerInterface.h"
#include "../Events/VelocityChangeEvent.h"
#include "Collisions/CollisionAwareInterface.h"

namespace Barta {

template<typename CollisionEventType>
class CollisionResponseSubscriber: public EventSubscriber<CollisionEventType> {
public:
    static constexpr float COEFFICIENT_OF_RESTITUTION = 1.f;

    CollisionResponseSubscriber(
        BartaEventLoggerInterface& eventLogger
    ):
        eventLogger(eventLogger) {}

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

        const auto& firstDynamics = firstObject->getDynamicsDTO();
        const auto& secondDynamics = secondObject->getDynamicsDTO();

        float massInverted = 0.f;
        if (!firstDynamics.hasInfiniteMass) {
            massInverted += (1.f / firstDynamics.mass);
        }

        if (!secondDynamics.hasInfiniteMass) {
            massInverted += (1.f / secondDynamics.mass);
        }

        if (massInverted == 0.f) {
            return true;
        }

        auto realFirstVelocity = firstDynamics.velocity + testResult.timePassed * firstDynamics.acceleration;
        auto realSecondVelocity = secondDynamics.velocity + testResult.timePassed * secondDynamics.acceleration;
        auto j = -(1.f + COEFFICIENT_OF_RESTITUTION) * ((realSecondVelocity - realFirstVelocity) * testResult.normVector)
                 / (testResult.normVector * testResult.normVector * massInverted);
        this->calculateNewVelocity(-j, firstObject, testResult.normVector);
        this->calculateNewVelocity(j, secondObject, testResult.normVector);

        return true;
    }

    bool isValid() const noexcept override { return true; }

private:
    BartaEventLoggerInterface& eventLogger;

    void calculateNewVelocity(
        float j,
        CollisionAwareInterface* dynamicsObject,
        Vector2f normVector
    ) const noexcept {
        const auto& oldDynamics = dynamicsObject->getDynamicsDTO();
        if (oldDynamics.hasInfiniteMass) {
            return;
        }

        this->eventLogger.logEvent(DynamicsChangeEvent(dynamicsObject, normVector * (j / oldDynamics.mass)));
    }
};

template<typename T1, typename T2>
using StaticCollisionResponseSubscriberType = CollisionResponseSubscriber<CollisionEvent<T1, T2>>;
}
