#include <Hitbox/CircleHitbox.h>
#include "Geometrics/BartaShapes/TriangleSurface.h"
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
    CollectionStrategyAggregator& collectionStrategyAggregator
) const {
    return collectionStrategyAggregator.acceptCheckCollisionVisitor(CircleCircleCheckCollisionVisitor(secondCircle, this->getCircle()));
}

CollisionTestResult CircleHitbox::intersectsWithAABB(
    const AABB& secondAABB,
    CollectionStrategyAggregator& collectionStrategyAggregator
) const {
    return collectionStrategyAggregator.swapObjects()
        .acceptCheckCollisionVisitor(CircleAABBCheckCollisionVisitor(this->getCircle(), secondAABB))
        .swapObjects();
}

CollisionTestResult CircleHitbox::intersectsWithOBB(
    const OBB& obb,
    CollectionStrategyAggregator& collectionStrategyAggregator
) const {
    auto rebaseMatrix = obb.getTransformation().getMatrix().inverse();
    auto collisionResult = collectionStrategyAggregator.applyTransform(rebaseMatrix)
                               .swapObjects()
                               .acceptCheckCollisionVisitor(CircleAABBCheckCollisionVisitor(
                                   rebaseMatrix * Circle(this->circle.getRadius(), this->circle.getCenter()),
                                   rebaseMatrix * AABB(obb.getFirstVertex(), obb.getWidthHeight())
                               ));
    if (collisionResult.collisionDetected) {
        collisionResult.collisionPoint = obb.getTransformation().getMatrix() * collisionResult.collisionPoint;
        collisionResult.normVector = obb.getTransformation().getMatrix() * collisionResult.normVector;
    }

    return collisionResult;
}

CollisionTestResult CircleHitbox::intersectsWithTriangleAggregated(
    const Geometrics::BartaShapes::TriangleSurface& secondShape,
    CollectionStrategyAggregator& collectionStrategyAggregator
) const {
    throw std::runtime_error("Not implemented");
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
    CollectionStrategyAggregator& collectionStrategyAggregator
) const {
    return secondHitbox.intersectsWithCircle(this->getCircle(), collectionStrategyAggregator);
}

std::unique_ptr<const HitboxInterface> CircleHitbox::getTransformedHitbox(
    const Transformation& transformation
) const {
    return std::make_unique<const CircleHitbox>(transformation.getMatrix() * this->circle);
}
}
