#pragma once
#include "../Dynamics/TimerInterface.h"
#include "../pch.h"
#include <Collisions/CollisionTestResult/CollisionTestResult.h>
#include <Collisions/CollisionTestResult/CollisionTestResultBuilder.h>

namespace Barta {
class CheckCollisionVisitorInterface {
public:
    CheckCollisionVisitorInterface() = default;
    virtual ~CheckCollisionVisitorInterface() = default;

    virtual CollisionTestResult checkStaticCollision(CollisionTestResultBuilder& collisionTestResultBuilder) const = 0;

    virtual CollisionTestResult checkDynamicCollision(PrecisionType delta_time, CollisionTestResultBuilder& collisionTestResultBuilder) const = 0;
};
}
