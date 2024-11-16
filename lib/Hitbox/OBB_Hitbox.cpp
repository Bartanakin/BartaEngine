//
// Created by bartanakin on 10/27/24.
//

#include "Collisions/CheckCollisionVisitors/OBB_AABBCheckCollisionVisitor.h"
#include "Hitbox/OBB_Hitbox.h"
#include <Collisions/CheckCollisionVisitors/CircleAABBCheckCollisionVisitor.h>
#include <Geometrics/Intersections.h>

Barta::OBB_Hitbox::OBB_Hitbox(
    const OBB& obb
) noexcept:
    obb(obb) {}

bool Barta::OBB_Hitbox::isWithin(
    const Vector2f& position
) const {
    auto rebasedPosition = this->obb.rebasePoint(position);

    return 0.f <= rebasedPosition.getX() && rebasedPosition.getX() <= this->obb.getWidthHeight().x && 0.f <= rebasedPosition.getY()
           && rebasedPosition.getY() <= this->obb.getWidthHeight().y;
}

std::vector<float> Barta::OBB_Hitbox::intersectsWithRay(
    const Ray& ray
) const {
    throw std::runtime_error("Not implemented");
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

    auto collisionResult = collisionDetector.acceptCheckCollisionVisitor(OBB_AABBCheckCollisionVisitor(obb, aabb, rebasedDynamicsDifference));
    if (collisionResult.collisionDetected) {
        collisionResult.collisionPoint = collisionResult.collisionPoint.rotated(secondShape.getRotation()) + secondShape.getFirstVertex();
        collisionResult.normVector = collisionResult.normVector.rotated(secondShape.getRotation());
    }

    return collisionResult;
}

Barta::OBB Barta::OBB_Hitbox::getBoundingOBB() const {
    return this->obb;
}
