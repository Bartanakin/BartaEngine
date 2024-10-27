#include <Hitbox/AABB_Hitbox.h>
#include <Collisions/CheckCollisionVisitors/AABB_AABBCheckCollisionVisitor.h>
#include <Collisions/CheckCollisionVisitors/CircleAABBCheckCollisionVisitor.h>
#include <pch.h>

#include "Collisions/CheckCollisionVisitors/OBB_AABBCheckCollisionVisitor.h"

Barta::AABB_Hitbox::AABB_Hitbox(
    const AABB& aabb
):
    aabb(aabb) {}

bool Barta::AABB_Hitbox::isWithin(
    const Vector2f& position
) const {
    return this->getAABB().getLeftTop().getX() <= position.getX() && position.getX() <= this->getAABB().getRightBottom().getX()
           && this->getAABB().getLeftTop().getY() <= position.getY() && position.getY() <= this->getAABB().getRightBottom().getY();
}

Barta::CollisionTestResult Barta::AABB_Hitbox::intersects(
    const HitboxInterface& secondHitbox,
    const CollisionDetectionStrategyInterface& collisionDetector,
    const DynamicsDifference& dynamicsDifference
) const {
    return secondHitbox.intersectsWithAABB(this->getAABB(), collisionDetector, dynamicsDifference);
}

std::unique_ptr<const Barta::HitboxInterface> Barta::AABB_Hitbox::getTransformedHitbox(
    const TransformableInterface& transformable
) const {
    return std::unique_ptr<const HitboxInterface>(new AABB_Hitbox(transformable.getTransformedAABB(this->getAABB())));
}

Barta::CollisionTestResult Barta::AABB_Hitbox::intersectsWithCircle(
    const Circle& secondCircle,
    const CollisionDetectionStrategyInterface& collisionDetector,
    const DynamicsDifference& dynamicsDifference
) const {
    return collisionDetector.acceptCheckCollisionVisitor(CircleAABBCheckCollisionVisitor(secondCircle, this->getAABB(), dynamicsDifference));
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

Barta::CollisionTestResult Barta::AABB_Hitbox::intersectsWithAABB(
    const AABB& secondAABB,
    const CollisionDetectionStrategyInterface& collisionDetector,
    const DynamicsDifference& dynamicsDifference
) const {
    return collisionDetector.acceptCheckCollisionVisitor(AABB_AABBCheckCollisionVisitor(secondAABB, this->getAABB(), dynamicsDifference));
}

Barta::CollisionTestResult Barta::AABB_Hitbox::intersectsWithOBB(
    const OBB& secondShape,
    const CollisionDetectionStrategyInterface& collisionDetector,
    const DynamicsDifference& dynamicsDifference
) const {
    return collisionDetector.acceptCheckCollisionVisitor(OBB_AABBCheckCollisionVisitor(secondShape, this->aabb, dynamicsDifference));
}

#pragma GCC diagnostic pop

const Barta::AABB& Barta::AABB_Hitbox::getAABB() const {
    return this->aabb;
}
