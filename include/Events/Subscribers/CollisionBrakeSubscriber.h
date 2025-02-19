//
// Created by bartanakin on 11/2/24.
//

#pragma once
#include <Dynamics/DynamicsAwareListConcept.h>
#include <Events/BartaEventLoggerInterface.h>
#include <Events/Events/CollisionEvent.h>

namespace Barta {

template<DynamicsAwareConcept T1, DynamicsAwareConcept T2>
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
