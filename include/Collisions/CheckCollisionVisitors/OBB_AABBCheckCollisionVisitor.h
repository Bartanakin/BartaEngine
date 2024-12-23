//
// Created by bartanakin on 10/27/24.
//

#pragma once
#include "Geometrics/BartaShapes/OBB.h"
#include <Collisions/CheckCollisionVisitorInterface.h>
#include <Dynamics/DynamicsDifference.h>

namespace Barta {
class OBB_AABBCheckCollisionVisitor: public CheckCollisionVisitorInterface {
public:
    OBB_AABBCheckCollisionVisitor(const OBB& obb, const AABB& aabb, const DynamicsDifference& dynamicsDifference) noexcept;

    CollisionTestResult checkStaticCollision(CollisionTestResultBuilder& collisionTestResultBuilder) const override;

    CollisionTestResult checkDynamicCollision(float deltaTime, CollisionTestResultBuilder& collisionTestResultBuilder) const override;
    Vector2f calculateCollisionPoint() const;

private:
    static bool checkStaticOneWay(const AABB& aabb, const OBB& obb);

    const OBB obb;
    const AABB aabb;
    const DynamicsDifference dynamicsDifference;
};
}
