#pragma once
#include <Collisions/CollisionDetectionStrategyInterface.h>
#include <Dynamics/DynamicsDifference.h>
#include <Geometrics/BartaShapes/OBB.h>
#include <Geometrics/Ray.h>
#include <pch.h>

namespace Barta {

class HitboxInterface {
public:
    HitboxInterface() = default;
    virtual ~HitboxInterface() = default;

    virtual bool isWithin(const Point& position) const = 0;

    virtual std::vector<float> intersectsWithRay(const Ray& ray) const = 0;

    virtual CollisionTestResult intersects(
        const HitboxInterface& secondHitbox,
        const CollisionDetectionStrategyInterface& collisionDetector,
        const DynamicsDifference& dynamicsDifference
    ) const = 0;

    virtual std::unique_ptr<const HitboxInterface> getTransformedHitbox(const Transformation& transformation) const = 0;

    virtual CollisionTestResult intersectsWithCircle(
        const Circle& secondHitbox,
        const CollisionDetectionStrategyInterface& collisionDetector,
        const DynamicsDifference& dynamicsDifference
    ) const = 0;

    virtual CollisionTestResult intersectsWithAABB(
        const AABB& secondHitbox,
        const CollisionDetectionStrategyInterface& collisionDetector,
        const DynamicsDifference& dynamicsDifference
    ) const = 0;

    virtual CollisionTestResult intersectsWithOBB(
        const OBB& secondShape,
        const CollisionDetectionStrategyInterface& collisionDetector,
        const DynamicsDifference& dynamicsDifference
    ) const = 0;

    virtual OBB getBoundingOBB() const = 0;
};

}
