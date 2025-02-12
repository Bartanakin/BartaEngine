#include <Hitbox/CircleHitbox.h>
#include <Collisions/CheckCollisionVisitors/CircleAABBCheckCollisionVisitor.h>
#include <Collisions/CheckCollisionVisitors/CircleCircleCheckCollisionVisitor.h>
#include <Geometrics/Intersections.h>
#include <pch.h>

namespace Barta {
class AABB_Hitbox;

CircleHitbox::CircleHitbox(
    const Circle& circle
):
    circle(circle) {}

const Circle& CircleHitbox::getCircle() const {
    return this->circle;
}

CollisionTestResult CircleHitbox::intersectsWithCircle(
    const Circle& secondCircle,
    const CollisionDetectionStrategyInterface& collisionDetector,
    const DynamicsDifference& dynamicsDifference
) const {
    return collisionDetector.acceptCheckCollisionVisitor(CircleCircleCheckCollisionVisitor(secondCircle, this->getCircle(), dynamicsDifference));
}

CollisionTestResult CircleHitbox::intersectsWithAABB(
    const AABB& secondAABB,
    const CollisionDetectionStrategyInterface& collisionDetector,
    const DynamicsDifference& dynamicsDifference
) const {
    return collisionDetector.acceptCheckCollisionVisitor(CircleAABBCheckCollisionVisitor(this->getCircle(), secondAABB, -dynamicsDifference));
}

CollisionTestResult CircleHitbox::intersectsWithOBB(
    const OBB& obb,
    const CollisionDetectionStrategyInterface& collisionDetector,
    const DynamicsDifference& dynamicsDifference
) const {
    auto rebasedDynamicsDifference = DynamicsDifference(
        obb.rebaseVector(dynamicsDifference.velocity),
        obb.rebasePoint(dynamicsDifference.acceleration),
        dynamicsDifference.rotationVelocity
    );
    auto collisionResult = collisionDetector.acceptCheckCollisionVisitor(CircleAABBCheckCollisionVisitor(
        {this->circle.getRadius(), obb.rebasePoint(this->circle.getCenter())},
        {obb.rebasePoint(obb.getFirstVertex()), obb.getWidthHeight()},
        rebasedDynamicsDifference
    ));
    if (collisionResult.collisionDetected) {
        collisionResult.collisionPoint = collisionResult.collisionPoint.rotated(obb.getRotation()) + obb.getFirstVertex();
        collisionResult.normVector = collisionResult.normVector.rotated(obb.getRotation());
    }

    return collisionResult;
}

OBB CircleHitbox::getBoundingOBB() const {
    return {
        this->getCircle().getCenter() - this->getCircle().getRadius() * Vector2f(1.f, 1.f),
        2.f * this->getCircle().getRadius() * Vector2f(1.f, 1.f),
        0.f
    };
}

bool CircleHitbox::isWithin(
    const Vector2f& position
) const {
    return pow(position.getX() - this->circle.getCenter().getX(), 2) + pow(position.getY() - this->circle.getCenter().getY(), 2)
           <= pow(this->circle.getRadius(), 2);
}

std::vector<float> CircleHitbox::intersectsWithRay(
    const Ray& ray
) const {
    return Intersections::rayAndCircle(ray, this->circle);
}

CollisionTestResult CircleHitbox::intersects(
    const HitboxInterface& secondHitbox,
    const CollisionDetectionStrategyInterface& collisionDetector,
    const DynamicsDifference& dynamicsDifference
) const {
    return secondHitbox.intersectsWithCircle(this->getCircle(), collisionDetector, dynamicsDifference);
}

std::unique_ptr<const HitboxInterface> CircleHitbox::getTransformedHitbox(
    const TransformableInterface& transformable
) const {
    return std::make_unique<const CircleHitbox>(transformable.getTransformedCircle(this->circle));
}
}
