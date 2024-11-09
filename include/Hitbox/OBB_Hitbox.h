//
// Created by bartanakin on 10/27/24.
//

#pragma once
#include "Geometrics/BartaShapes/OBB.h"
#include "HitboxInterface.h"

namespace Barta {
class OBB_Hitbox: public virtual HitboxInterface {
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

    const OBB& getOBB() const noexcept { return this->obb; }

    OBB getBoundingOBB() const override;

private:
    OBB obb;
};
}
