#pragma once

#include <Collisions/CheckCollisionVisitorInterface.h>
#include <Collisions/CollisionTestResult/CollisionTestResult.h>
#include <Collisions/CollisionTestResult/CollisionTestResultBuilder.h>
#include <Dynamics/DynamicsDTO.h>
#include <Geometrics/BartaShapes/AABB.h>
#include <pch.h>

namespace Barta {

class AABB_AABBCheckCollisionVisitor: public CheckCollisionVisitorInterface {
public:
    AABB_AABBCheckCollisionVisitor(const AABB& aabb1, const AABB& aabb2, const DynamicsDifference& dynamicsDifference) noexcept;

    CollisionTestResult checkStaticCollision(CollisionTestResultBuilder& collisionTestResultBuilder) const override;

    CollisionTestResult checkDynamicCollision(PrecisionType delta_time, CollisionTestResultBuilder& collisionTestResultBuilder) const override;

private:
    const AABB aabb1;
    const AABB aabb2;
    const DynamicsDifference dynamicsDifference;

    Point calculateCollisionPoint() const;
};
}
