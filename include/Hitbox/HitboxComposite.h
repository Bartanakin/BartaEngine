#pragma once
#include "../Geometrics/TransformableInterface.h"
#include "HitboxInterface.h"

namespace Barta {

class HitboxComposite final: public HitboxInterface {
public:
    using HitboxesList = std::vector<std::unique_ptr<const HitboxInterface>>;

    explicit HitboxComposite(HitboxesList children);
    ~HitboxComposite() override = default;

    bool isWithin(const Vector2f& position) const override;

    CollisionTestResult intersects(
        const HitboxInterface& secondHitbox,
        const CollisionDetectionStrategyInterface& collisionDetector,
        const DynamicsDTO& dynamicsDifference
    ) const override;

    std::unique_ptr<const HitboxInterface> getTransformedHitbox(const TransformableInterface& transformable) const override;

    CollisionTestResult intersectsWithCircle(
        const Circle& secondCircle,
        const CollisionDetectionStrategyInterface& collisionDetector,
        const DynamicsDTO& dynamicsDifference
    ) const override;

    CollisionTestResult intersectsWithAABB(
        const AABB& secondAABB,
        const CollisionDetectionStrategyInterface& collisionDetector,
        const DynamicsDTO& dynamicsDifference
    ) const override;

private:
    HitboxesList children;
};

}
