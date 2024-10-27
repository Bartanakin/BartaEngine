//
// Created by bartanakin on 10/27/24.
//

#include "Collisions/CheckCollisionVisitors/OBB_AABBCheckCollisionVisitor.h"
#include "Hitbox/OBB_Hitbox.h"
#include <Collisions/CheckCollisionVisitors/CircleAABBCheckCollisionVisitor.h>

Barta::OBB_Hitbox::OBB_Hitbox(
    const OBB& obb
) noexcept:
    AABB_Hitbox(obb.getAABB()),
    obb(obb) {}

bool Barta::OBB_Hitbox::isWithin(
    const Vector2f& position
) const {
    return AABB_Hitbox::isWithin(this->obb.rebasePoint(position));
}

Barta::CollisionTestResult Barta::OBB_Hitbox::intersects(
    const HitboxInterface& secondHitbox,
    const CollisionDetectionStrategyInterface& collisionDetector,
    const DynamicsDifference& dynamicsDifference
) const {
    return secondHitbox.intersectsWithOBB(this->obb, collisionDetector, dynamicsDifference);
}

std::unique_ptr<const Barta::HitboxInterface> Barta::OBB_Hitbox::getTransformedHitbox(
    const TransformableInterface& transformable
) const {
    return std::make_unique<const OBB_Hitbox>(transformable.getTransformedOBB(this->obb));
}

Barta::CollisionTestResult Barta::OBB_Hitbox::intersectsWithCircle(
    const Circle& circle,
    const CollisionDetectionStrategyInterface& collisionDetector,
    const DynamicsDifference& dynamicsDifference
) const {
    auto rebasedDynamicsDifference = DynamicsDifference(
        this->obb.rebasePoint(dynamicsDifference.velocity),
        this->obb.rebasePoint(dynamicsDifference.acceleration),
        dynamicsDifference.rotationVelocity
    );
    return collisionDetector.acceptCheckCollisionVisitor(CircleAABBCheckCollisionVisitor(
        {circle.getRadius(), this->obb.rebasePoint(circle.getCenter())},
        {this->obb.rebasePoint(this->obb.getFirstVertex()), this->obb.getWidthHeight()},
        rebasedDynamicsDifference
    ));
}

Barta::CollisionTestResult Barta::OBB_Hitbox::intersectsWithAABB(
    const AABB& aabb,
    const CollisionDetectionStrategyInterface& collisionDetector,
    const DynamicsDifference& dynamicsDifference
) const {
    return collisionDetector.acceptCheckCollisionVisitor(OBB_AABBCheckCollisionVisitor(this->obb, aabb, dynamicsDifference));
}

Barta::CollisionTestResult Barta::OBB_Hitbox::intersectsWithOBB(
    const OBB& secondShape,
    const CollisionDetectionStrategyInterface& collisionDetector,
    const DynamicsDifference& dynamicsDifference
) const {
    // REBASE ! TODO rebase back
    auto rebasedDynamicsDifference = DynamicsDifference(
        this->obb.rebaseVector(dynamicsDifference.velocity),
        this->obb.rebaseVector(dynamicsDifference.acceleration),
        dynamicsDifference.rotationVelocity
    );

    auto aabb = AABB({}, secondShape.getWidthHeight());
    auto obb =
        OBB((this->obb.getFirstVertex() - secondShape.getFirstVertex()).rotated(-secondShape.getRotation()),
            this->obb.getWidthHeight(),
            this->obb.getRotation() - secondShape.getRotation());

    return collisionDetector.acceptCheckCollisionVisitor(OBB_AABBCheckCollisionVisitor(obb, aabb, rebasedDynamicsDifference));
}
