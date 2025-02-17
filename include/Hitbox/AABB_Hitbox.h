#pragma once
#include <Dynamics/DynamicsDifference.h>
#include <Geometrics/BartaShapes/OBB.h>
#include <Hitbox/HitboxInterface.h>
#include <pch.h>

namespace Barta {

class AABB_Hitbox: public HitboxInterface {
public:
    AABB_Hitbox(const AABB& aabb);
    ~AABB_Hitbox() = default;

    bool isWithin(const Point& position) const override;

    std::vector<float> intersectsWithRay(const Ray& ray) const override;

    CollisionTestResult intersects(
        const HitboxInterface& secondHitbox,
        const CollisionDetectionStrategyInterface& collisionDetector,
        const DynamicsDifference& dynamicsDifference
    ) const override;

    std::unique_ptr<const HitboxInterface> getTransformedHitbox(const Transformation& transformation) const override;

    CollisionTestResult intersectsWithCircle(
        const Circle& secondCircle,
        const CollisionDetectionStrategyInterface& collisionDetector,
        const DynamicsDifference& dynamicsDifference
    ) const override;

    CollisionTestResult intersectsWithAABB(
        const AABB& secondAABB,
        const CollisionDetectionStrategyInterface& collisionDetector,
        const DynamicsDifference& dynamicsDifference
    ) const override;

    CollisionTestResult intersectsWithOBB(
        const OBB& secondShape,
        const CollisionDetectionStrategyInterface& collisionDetector,
        const DynamicsDifference& dynamicsDifference
    ) const override;

    OBB getBoundingOBB() const override;

private:
    const AABB& getAABB() const;

    const AABB aabb;
};

}
