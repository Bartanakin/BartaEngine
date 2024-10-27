//
// Created by bartanakin on 10/27/24.
//

#pragma once
#include "AABB_Hitbox.h"
#include "Geometrics/BartaShapes/OBB.h"
#include "HitboxInterface.h"

namespace Barta {
class OBB_Hitbox: public AABB_Hitbox {
public:
    OBB_Hitbox(const OBB& obb) noexcept;
    bool isWithin(const Vector2f& position) const override;

    CollisionTestResult intersects(
        const HitboxInterface& secondHitbox,
        const CollisionDetectionStrategyInterface& collisionDetector,
        const DynamicsDifference& dynamicsDifference
    ) const override;

    std::unique_ptr<const HitboxInterface> getTransformedHitbox(const TransformableInterface& transformable) const override;

    CollisionTestResult intersectsWithCircle(
        const Circle& secondHitbox,
        const CollisionDetectionStrategyInterface& collisionDetector,
        const DynamicsDifference& dynamicsDifference
    ) const override;

    CollisionTestResult intersectsWithAABB(
        const AABB& secondHitbox,
        const CollisionDetectionStrategyInterface& collisionDetector,
        const DynamicsDifference& dynamicsDifference
    ) const override;

    CollisionTestResult intersectsWithOBB(
        const OBB& secondShape,
        const CollisionDetectionStrategyInterface& collisionDetector,
        const DynamicsDifference& dynamicsDifference
    ) const override;

private:
    OBB obb;
};
}
