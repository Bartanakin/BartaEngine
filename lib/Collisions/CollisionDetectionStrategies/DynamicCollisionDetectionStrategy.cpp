#include <Collisions/CollisionDetectionStrategies/DynamicCollisionDetectionStrategy.h>

Barta::DynamicCollisionDetectionStrategy::DynamicCollisionDetectionStrategy(
    const TimerInterface& timer
):
    timer(timer) {}

Barta::CollisionTestResult Barta::DynamicCollisionDetectionStrategy::acceptCheckCollisionVisitor(
    const CheckCollisionVisitorInterface& checkCollisionVisitor,
    const DynamicsDTOCollection& dynamicsOfFirstObject,
    const DynamicsDTOCollection& dynamicsOfSecondObject
) const {
    auto staticTestResult = checkCollisionVisitor.checkStaticCollision(dynamicsOfFirstObject, dynamicsOfSecondObject);
    if (staticTestResult.collisionDetected) {
        return staticTestResult;
    }

    return checkCollisionVisitor.checkDynamicCollision(this->timer.getCurrentDeltaTime(), dynamicsOfFirstObject, dynamicsOfSecondObject);
}
