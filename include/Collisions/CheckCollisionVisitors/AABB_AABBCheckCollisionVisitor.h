#pragma once

#include "../../Dynamics/DynamicsDTO.h"
#include "../../Geometrics/BartaShapes/AABB.h"
#include "../../pch.h"
#include "../CheckCollisionVisitorInterface.h"
#include <Collisions/CollisionTestResult/CollisionTestResult.h>
#include <Collisions/CollisionTestResult/CollisionTestResultBuilder.h>

namespace Barta {

class AABB_AABBCheckCollisionVisitor: public CheckCollisionVisitorInterface {
public:
    AABB_AABBCheckCollisionVisitor(const AABB& aabb1, const AABB& aabb2, const DynamicsDifference& dynamicsDifference) noexcept;

    CollisionTestResult checkStaticCollision(const MathLibraryInterface& mathLib, CollisionTestResultBuilder& collisionTestResultBuilder)
        const override;

    CollisionTestResult checkDynamicCollision(
        const MathLibraryInterface& mathLib,
        float delta_time,
        CollisionTestResultBuilder& collisionTestResultBuilder
    ) const override;

private:
    const AABB aabb1;
    const AABB aabb2;
    const DynamicsDifference dynamicsDifference;

    Vector2f calculateCollisionPoint() const;
};
}
