#include <Collisions/CollisionDetectionStrategies/DynamicCollisionDetectionStrategy.h>
#include "pch.h"

Barta::DynamicCollisionDetectionStrategy::DynamicCollisionDetectionStrategy(
    const TimerInterface& timer
):
    timer(timer) {}

Barta::CollisionTestResult Barta::DynamicCollisionDetectionStrategy::acceptCheckCollisionVisitor(
    const CheckCollisionVisitorInterface& checkCollisionVisitor
) const {
    auto builder = CollisionTestResultBuilder();

    return checkCollisionVisitor.checkDynamicCollision(this->timer.getCurrentDeltaTime(), builder);
}
