#pragma once
#include <Dynamics/UpdateStrategy/DynamicsAwareConcept.h>
#include <Events/BartaEventLoggerInterface.h>
#include <Events/Events/CollisionEvent.h>

namespace Barta {

template<Dynamics::UpdateStrategy::DynamicsAwareConcept T1, Dynamics::UpdateStrategy::DynamicsAwareConcept T2>
class CollisionBrakeSubscriber: public virtual EventSubscriber<CollisionEvent<T1, T2>> {
public:
    CollisionBrakeSubscriber() noexcept {}

    bool handle(
        CollisionEvent<T1, T2>& event
    ) {
        if (!event.collisionResult.object1->getDynamicsDTOs()[DynamicsDTOIteration::NEXT].hasInfiniteMass) {
            event.getTestResult().object1->getDynamicsDTOs()[DynamicsDTOIteration::NEXT].allowedDirections.push_back(
                event.getTestResult().collisionTestResult.normVector
            );
        }

        if (!event.collisionResult.object2->getDynamicsDTOs()[DynamicsDTOIteration::NEXT].hasInfiniteMass) {
            event.getTestResult().object2->getDynamicsDTOs()[DynamicsDTOIteration::NEXT].allowedDirections.push_back(
                -event.getTestResult().collisionTestResult.normVector
            );
        }

        return false;
    }

    bool isToBeDeleted() const noexcept { return false; }

private:
};
}
