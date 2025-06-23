#pragma once
#include <Collisions/CheckCollisionVisitorInterface.h>
#include <Geometrics/BartaShapes/AABB.h>
#include <Geometrics/BartaShapes/Circle.h>
#include <pch.h>

namespace Barta {

class CircleAABBCheckCollisionVisitor: public CheckCollisionVisitorInterface {
public:
    CircleAABBCheckCollisionVisitor(const Circle& circle, const AABB& aabb);
    virtual ~CircleAABBCheckCollisionVisitor();

    CollisionTestResult checkStaticCollision(const DynamicsDTOCollection& dynamicsOfFirstObject, const DynamicsDTOCollection& dynamicsOfSecondObject)
        const override;

    CollisionTestResult checkDynamicCollision(
        PrecisionType delta_time,
        const DynamicsDTOCollection& dynamicsOfFirstObject,
        const DynamicsDTOCollection& dynamicsOfSecondObject
    ) const override;

private:
    const Circle circle;
    const AABB aabb;
    const AABB expandedAABB;

    Point calculateCollisionPoint() const;
    Point matchCornerCenter(AABB::VoronoiRegion regionMask, const AABB& aabb) const;
    Vector calculateNormVector(const Vector& velocity) const;
    Vector calculateNormVectorForStatic() const;
};
}
