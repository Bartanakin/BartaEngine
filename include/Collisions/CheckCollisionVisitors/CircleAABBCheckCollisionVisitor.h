#pragma once
#include <Collisions/CheckCollisionVisitorInterface.h>
#include <Dynamics/DynamicsDifference.h>
#include <Geometrics/BartaShapes/AABB.h>
#include <Geometrics/BartaShapes/Circle.h>
#include <pch.h>

namespace Barta {

class CircleAABBCheckCollisionVisitor: public CheckCollisionVisitorInterface {
public:
    CircleAABBCheckCollisionVisitor(const Circle& circle, const AABB& aabb, const DynamicsDifference& dynamicsDifference);
    virtual ~CircleAABBCheckCollisionVisitor();

    CollisionTestResult checkStaticCollision(CollisionTestResultBuilder& collisionTestResultBuilder) const override;

    CollisionTestResult checkDynamicCollision(float delta_time, CollisionTestResultBuilder& collisionTestResultBuilder) const override;

private:
    const Circle circle;
    const AABB aabb;
    const DynamicsDifference dynamicsDifference;
    const AABB expandedAABB;

    Point calculateCollisionPoint() const;
    Point matchCornerCenter(AABB::VoronoiRegion regionMask, const AABB& aabb) const;
    Vector calculateNormVector(PrecisionType delta_time) const;
    Vector calculateNormVectorForStatic() const;
};
}
