//
// Created by bartanakin on 10/27/24.
//

#pragma once
#include <Collisions/CheckCollisionVisitorInterface.h>
#include <Geometrics/BartaShapes/OBB.h>

namespace Barta {
class OBB_AABBCheckCollisionVisitor: public CheckCollisionVisitorInterface {
public:
    OBB_AABBCheckCollisionVisitor(const OBB& obb, const AABB& aabb) noexcept;

    CollisionTestResult checkStaticCollision(const DynamicsDTOCollection& dynamicsOfFirstObject, const DynamicsDTOCollection& dynamicsOfSecondObject)
        const override;

    CollisionTestResult checkDynamicCollision(
        PrecisionType deltaTime,
        const DynamicsDTOCollection& dynamicsOfFirstObject,
        const DynamicsDTOCollection& dynamicsOfSecondObject
    ) const override;

    Point calculateCollisionPoint() const;

private:
    static bool checkStaticOneWay(const AABB& aabb, const OBB& obb);

    const OBB obb;
    const AABB aabb;
};
}
