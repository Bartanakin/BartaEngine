#pragma once
#include "../../Dynamics/DynamicsDTO.h"
#include "../../Geometrics/BartaShapes/AABB.h"
#include "../../Geometrics/BartaShapes/Circle.h"
#include "../../pch.h"
#include "../CheckCollisionVisitorInterface.h"

namespace Barta {

class CircleAABBCheckCollisionVisitor: public CheckCollisionVisitorInterface {
public:
    CircleAABBCheckCollisionVisitor(const Circle& circle, const AABB& aabb, const DynamicsDifference& dynamicsDifference);
    virtual ~CircleAABBCheckCollisionVisitor();

    CollisionTestResult checkStaticCollision(const MathLibraryInterface& mathLib, CollisionTestResultBuilder& collisionTestResultBuilder)
        const override;

    CollisionTestResult checkDynamicCollision(
        const MathLibraryInterface& mathLib,
        float delta_time,
        CollisionTestResultBuilder& collisionTestResultBuilder
    ) const override;

private:
    const Circle circle;
    const AABB aabb;
    const DynamicsDifference dynamicsDifference;
    const AABB expandedAABB;

    Vector2f matchCornerCenter(AABB::VoronoiRegion regionMask, const AABB& aabb) const;
    Vector2f calculateNormVector(float delta_time) const;
};
}
