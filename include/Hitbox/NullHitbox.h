#pragma once

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
        CollectionStrategyAggregator& collectionStrategyAggregator
    ) const override;

    std::unique_ptr<const HitboxInterface> getTransformedHitbox(const Transformation& transformation) const override;

    CollisionTestResult intersectsWithCircle(
        const Circle& secondCircle,
        CollectionStrategyAggregator& collectionStrategyAggregator
    ) const override;

    CollisionTestResult intersectsWithAABB(
        const AABB& secondAABB,
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

    OBB getBoundingOBB() const override;
};

}
