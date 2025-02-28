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
    auto rebaseMatrix = obb.getTransformation().getMatrix().inverse();
    auto collisionResult = collisionDetector.acceptCheckCollisionVisitor(CircleAABBCheckCollisionVisitor(
        rebaseMatrix * Circle(this->circle.getRadius(), this->circle.getCenter()),
        rebaseMatrix * AABB(obb.getFirstVertex(), obb.getWidthHeight()),
        -rebaseMatrix * dynamicsDifference
    ));
    if (collisionResult.collisionDetected) {
        collisionResult.collisionPoint = obb.getTransformation().getMatrix() * collisionResult.collisionPoint;
        collisionResult.normVector = obb.getTransformation().getMatrix() * collisionResult.normVector;
    }

    return collisionResult;
}

// TODO third dimention
OBB CircleHitbox::getBoundingOBB() const {
    return {
        this->getCircle().getCenter() - this->getCircle().getRadius() * Vector(1.f, 1.f),
        2.f * this->getCircle().getRadius() * Vector(1.f, 1.f),
        0.f
    };
}

bool CircleHitbox::isWithin(
    const Point& position
) const {
    return pow(position.x() - this->circle.getCenter().x(), 2) + pow(position.y() - this->circle.getCenter().y(), 2)
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
    const Transformation& transformation
) const {
    return std::make_unique<const CircleHitbox>(transformation.getMatrix() * this->circle);
}
}
