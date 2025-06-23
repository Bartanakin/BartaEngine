#pragma once
#include "Geometrics/BartaShapes/TriangleSurface.h"
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

    CollisionTestResult intersects(const HitboxInterface& secondHitbox, CollectionStrategyAggregator& collectionStrategyAggregator)
        const override;

    std::unique_ptr<const HitboxInterface> getTransformedHitbox(const Transformation& transformation) const override;

    CollisionTestResult intersectsWithCircle(const Circle& secondCircle, CollectionStrategyAggregator& collectionStrategyAggregator)
        const override;

    CollisionTestResult intersectsWithAABB(const AABB& secondAABB, CollectionStrategyAggregator& collectionStrategyAggregator) const override;

    CollisionTestResult intersectsWithOBB(const OBB& secondShape, CollectionStrategyAggregator& collectionStrategyAggregator) const override;

    CollisionTestResult intersectsWithTriangleAggregated(
        const Geometrics::BartaShapes::TriangleSurface& secondShape,
        CollectionStrategyAggregator& collectionStrategyAggregator
    ) const override;

    OBB getBoundingOBB() const override;

private:
    const AABB& getAABB() const;

    const AABB aabb;
};

}
