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
    AABB_AABBCheckCollisionVisitor(const AABB& aabb1, const AABB& aabb2) noexcept;

    CollisionTestResult checkStaticCollision(const DynamicsDTOCollection& dynamicsOfFirstObject, const DynamicsDTOCollection& dynamicsOfSecondObject)
        const override;

    CollisionTestResult checkDynamicCollision(
        PrecisionType delta_time,
        const DynamicsDTOCollection& dynamicsOfFirstObject,
        const DynamicsDTOCollection& dynamicsOfSecondObject
    ) const override;

private:
    const AABB aabb1;
    const AABB aabb2;

    Point calculateCollisionPoint() const;
};
}
