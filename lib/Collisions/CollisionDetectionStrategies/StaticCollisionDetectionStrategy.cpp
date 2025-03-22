#include <Collisions/CollisionDetectionStrategies/StaticCollisionDetectionStrategy.h>
#include <Collisions/CollisionTestResult/CollisionTestResultBuilder.h>

Barta::StaticCollisionDetectionStrategy::StaticCollisionDetectionStrategy() {}

Barta::CollisionTestResult Barta::StaticCollisionDetectionStrategy::acceptCheckCollisionVisitor(
    const CheckCollisionVisitorInterface& checkCollisionVisitor
) const {
    auto builder = CollisionTestResultBuilder();

    return checkCollisionVisitor.checkStaticCollision(builder);
}
