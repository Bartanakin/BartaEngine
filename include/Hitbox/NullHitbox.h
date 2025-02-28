#pragma once

#include <Dynamics/DynamicsDifference.h>
#include <Geometrics/BartaShapes/OBB.h>
#include <Geometrics/Transformation.h>
#include <Hitbox/HitboxInterface.h>
#include <pch.h>

namespace Barta {

class NullHitbox final: public virtual HitboxInterface {
public:
    NullHitbox() = default;
    ~NullHitbox() override = default;

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
};

}
