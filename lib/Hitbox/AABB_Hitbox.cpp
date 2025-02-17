#include <Hitbox/AABB_Hitbox.h>
#include "Collisions/CheckCollisionVisitors/OBB_AABBCheckCollisionVisitor.h"
#include <Collisions/CheckCollisionVisitors/AABB_AABBCheckCollisionVisitor.h>
#include <Collisions/CheckCollisionVisitors/CircleAABBCheckCollisionVisitor.h>
#include <pch.h>

namespace Barta {
AABB_Hitbox::AABB_Hitbox(
    const AABB& aabb
):
    aabb(aabb) {}

bool AABB_Hitbox::isWithin(
    const Point& position
) const {
    return this->getAABB().getLeftTop().x() <= position.x() && position.x() <= this->getAABB().getRightBottom().x()
           && this->getAABB().getLeftTop().y() <= position.y() && position.y() <= this->getAABB().getRightBottom().y();
}

std::vector<float> AABB_Hitbox::intersectsWithRay(
    const Ray& ray
) const {
    // TODO
    return {};
}

CollisionTestResult AABB_Hitbox::intersects(
    const HitboxInterface& secondHitbox,
    const CollisionDetectionStrategyInterface& collisionDetector,
    const DynamicsDifference& dynamicsDifference
) const {
    return secondHitbox.intersectsWithAABB(this->getAABB(), collisionDetector, dynamicsDifference);
}

std::unique_ptr<const HitboxInterface> AABB_Hitbox::getTransformedHitbox(
    const Transformation& transformation
) const {
    return std::make_unique<const AABB_Hitbox>(transformation.getMatrix() * this->getAABB());
}

CollisionTestResult AABB_Hitbox::intersectsWithCircle(
    const Circle& secondCircle,
    const CollisionDetectionStrategyInterface& collisionDetector,
    const DynamicsDifference& dynamicsDifference
) const {
    return collisionDetector.acceptCheckCollisionVisitor(CircleAABBCheckCollisionVisitor(secondCircle, this->getAABB(), dynamicsDifference));
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

CollisionTestResult AABB_Hitbox::intersectsWithAABB(
    const AABB& secondAABB,
    const CollisionDetectionStrategyInterface& collisionDetector,
    const DynamicsDifference& dynamicsDifference
) const {
    return collisionDetector.acceptCheckCollisionVisitor(AABB_AABBCheckCollisionVisitor(secondAABB, this->getAABB(), dynamicsDifference));
}

CollisionTestResult AABB_Hitbox::intersectsWithOBB(
    const OBB& secondShape,
    const CollisionDetectionStrategyInterface& collisionDetector,
    const DynamicsDifference& dynamicsDifference
) const {
    return collisionDetector.acceptCheckCollisionVisitor(OBB_AABBCheckCollisionVisitor(secondShape, this->aabb, dynamicsDifference));
}

OBB AABB_Hitbox::getBoundingOBB() const {
    return {this->aabb.getLeftTop(), this->aabb.getWidthHeight(), 0.f};
}

#pragma GCC diagnostic pop

const AABB& AABB_Hitbox::getAABB() const {
    return this->aabb;
}
}
