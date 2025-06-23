#include <Collisions/CollisionDetectionStrategies/StaticCollisionDetectionStrategy.h>
#include <Collisions/CollisionTestResult/CollisionTestResultBuilder.h>

Barta::StaticCollisionDetectionStrategy::StaticCollisionDetectionStrategy() {}

Barta::CollisionTestResult Barta::StaticCollisionDetectionStrategy::acceptCheckCollisionVisitor(
    const CheckCollisionVisitorInterface& checkCollisionVisitor,
    const DynamicsDTOCollection& dynamicsOfFirstObject,
    const DynamicsDTOCollection& dynamicsOfSecondObject
) const {
    return checkCollisionVisitor.checkStaticCollision(dynamicsOfFirstObject, dynamicsOfSecondObject);
}
