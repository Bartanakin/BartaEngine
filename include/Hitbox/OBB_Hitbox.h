//
// Created by bartanakin on 10/27/24.
//

#pragma once
#include <Geometrics/BartaShapes/OBB.h>
#include <Hitbox/HitboxInterface.h>

namespace Barta {
class OBB_Hitbox: public virtual HitboxInterface {
public:
    OBB_Hitbox(const OBB& obb) noexcept;

    bool isWithin(const Point& position) const override;

    std::vector<float> intersectsWithRay(const Ray& ray) const override;

    CollisionTestResult intersects(
        const HitboxInterface& secondHitbox,
        CollectionStrategyAggregator& collectionStrategyAggregator
    ) const override;

    std::unique_ptr<const HitboxInterface> getTransformedHitbox(const Transformation& transformation) const override;

    CollisionTestResult intersectsWithCircle(
        const Circle& secondHitbox,
        CollectionStrategyAggregator& collectionStrategyAggregator
    ) const override;

    CollisionTestResult intersectsWithAABB(
        const AABB& secondHitbox,
        CollectionStrategyAggregator& collectionStrategyAggregator
    ) const override;

    CollisionTestResult intersectsWithOBB(
        const OBB& secondShape,
        CollectionStrategyAggregator& collectionStrategyAggregator
    ) const override;

    CollisionTestResult intersectsWithTriangleAggregated(
        const Geometrics::BartaShapes::TriangleSurface& secondShape,
        CollectionStrategyAggregator& collectionStrategyAggregator
    ) const override;

    const OBB& getOBB() const noexcept { return this->obb; }

    OBB getBoundingOBB() const override;

private:
    OBB obb;
};
}
