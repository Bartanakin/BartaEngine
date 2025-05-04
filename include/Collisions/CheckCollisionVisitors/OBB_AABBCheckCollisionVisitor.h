//
// Created by bartanakin on 10/27/24.
//

#pragma once
#include <Collisions/CheckCollisionVisitorInterface.h>
#include <Dynamics/DynamicsDifference.h>
#include <Geometrics/BartaShapes/OBB.h>

namespace Barta {
class OBB_AABBCheckCollisionVisitor: public CheckCollisionVisitorInterface {
public:
    OBB_AABBCheckCollisionVisitor(const OBB& obb, const AABB& aabb, const DynamicsDifference& dynamicsDifference) noexcept;

    CollisionTestResult checkStaticCollision(CollisionTestResultBuilder& collisionTestResultBuilder) const override;

    CollisionTestResult checkDynamicCollision(PrecisionType deltaTime, CollisionTestResultBuilder& collisionTestResultBuilder) const override;

    Point calculateCollisionPoint() const;

private:
    static bool checkStaticOneWay(const AABB& aabb, const OBB& obb);

    const OBB obb;
    const AABB aabb;
    const DynamicsDifference dynamicsDifference;
};
}
