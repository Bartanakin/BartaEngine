//
// Created by bartanakin on 10/27/24.
//

#include "Collisions/CheckCollisionVisitors/OBB_AABBCheckCollisionVisitor.h"
#include "Hitbox/OBB_Hitbox.h"
#include <Collisions/CheckCollisionVisitors/CircleAABBCheckCollisionVisitor.h>
#include <Geometrics/Intersections.h>
#include <Geometrics/Transformation.h>

namespace Barta {
OBB_Hitbox::OBB_Hitbox(
    const OBB& obb
) noexcept:
    obb(obb) {}

bool OBB_Hitbox::isWithin(
    const Point& position
) const {
    auto rebasedPosition = this->obb.getTransformation().getMatrix().inverse() * position;

    return 0.f <= rebasedPosition.x() && rebasedPosition.x() <= this->obb.getWidthHeight().x() && 0.f <= rebasedPosition.y()
           && rebasedPosition.y() <= this->obb.getWidthHeight().y();
}

std::vector<float> OBB_Hitbox::intersectsWithRay(
    const Ray& ray
) const {
    throw std::runtime_error("Not implemented");
}

CollisionTestResult OBB_Hitbox::intersects(
    const HitboxInterface& secondHitbox,
    CollectionStrategyAggregator& collectionStrategyAggregator
) const {
    return secondHitbox.intersectsWithOBB(this->obb, collectionStrategyAggregator);
}

std::unique_ptr<const HitboxInterface> OBB_Hitbox::getTransformedHitbox(
    const Transformation& transformation
) const {
    return std::make_unique<const OBB_Hitbox>(transformation.getMatrix() * this->obb);
}

CollisionTestResult OBB_Hitbox::intersectsWithCircle(
    const Circle& circle,
    CollectionStrategyAggregator& collectionStrategyAggregator
) const {
    auto inversedMatrix = this->obb.getTransformation().getMatrix().inverse();
    auto collisionResult =
        collectionStrategyAggregator.applyTransform(inversedMatrix)
            .acceptCheckCollisionVisitor(CircleAABBCheckCollisionVisitor(inversedMatrix * circle, AABB(Point::Zero(), obb.getWidthHeight())));

    if (collisionResult.collisionDetected) {
        collisionResult.normVector = this->obb.getTransformation().getMatrix() * collisionResult.normVector;
        collisionResult.collisionPoint = this->obb.getTransformation().getMatrix() * collisionResult.collisionPoint;
    }

    return collisionResult;
}

CollisionTestResult OBB_Hitbox::intersectsWithAABB(
    const AABB& aabb,
    CollectionStrategyAggregator& collectionStrategyAggregator
) const {
    return collectionStrategyAggregator.swapObjects().acceptCheckCollisionVisitor(OBB_AABBCheckCollisionVisitor(this->obb, aabb));
}

CollisionTestResult OBB_Hitbox::intersectsWithOBB(
    const OBB& secondShape,
    CollectionStrategyAggregator& collectionStrategyAggregator
) const {
    auto aabb = AABB(Point::Zero(), secondShape.getWidthHeight());
    auto obb = secondShape.getTransformation().getMatrix().inverse() * this->obb;

    auto collisionResult = collectionStrategyAggregator.applyTransform(this->obb.getTransformation().getMatrix().inverse())
                               .swapObjects()
                               .acceptCheckCollisionVisitor(OBB_AABBCheckCollisionVisitor(obb, aabb));
    if (collisionResult.collisionDetected) {
        collisionResult.collisionPoint = secondShape.getTransformation().getMatrix() * collisionResult.collisionPoint;
        collisionResult.normVector = secondShape.getTransformation().getMatrix() * collisionResult.normVector;
    }

    return collisionResult;
}

CollisionTestResult OBB_Hitbox::intersectsWithTriangleAggregated(
    const Geometrics::BartaShapes::TriangleSurface& secondShape,
    CollectionStrategyAggregator& collectionStrategyAggregator
) const {
    throw std::runtime_error("Not implemented");
}

OBB OBB_Hitbox::getBoundingOBB() const {
    return this->obb;
}
}
