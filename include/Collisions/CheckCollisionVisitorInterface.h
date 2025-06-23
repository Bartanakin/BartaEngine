#pragma once
#include "../Dynamics/TimerInterface.h"
#include "../pch.h"
#include "Dynamics/DynamicsDTOCollection.h"
#include <Collisions/CollisionTestResult/CollisionTestResult.h>

namespace Barta {
class CheckCollisionVisitorInterface {
public:
    CheckCollisionVisitorInterface() = default;
    virtual ~CheckCollisionVisitorInterface() = default;

    virtual CollisionTestResult checkStaticCollision(
        const DynamicsDTOCollection& dynamicsOfFirstObject,
        const DynamicsDTOCollection& dynamicsOfSecondObject
    ) const = 0;

    virtual CollisionTestResult checkDynamicCollision(
        PrecisionType delta_time,
        const DynamicsDTOCollection& dynamicsOfFirstObject,
        const DynamicsDTOCollection& dynamicsOfSecondObject
    ) const = 0;
};
}
