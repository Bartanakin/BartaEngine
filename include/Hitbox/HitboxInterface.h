#pragma once
#include "Collisions/CollisionDetectionStrategies/CollectionStrategyAggregator.h"
#include "Geometrics/BartaShapes/TriangleSurface.h"
#include <Collisions/CollisionDetectionStrategyInterface.h>
#include <Geometrics/BartaShapes/OBB.h>
#include <Geometrics/Ray.h>
#include <pch.h>

namespace Barta {
using namespace Collisions::CollisionDetectionStrategies;

class HitboxInterface {
public:
    HitboxInterface() = default;
    virtual ~HitboxInterface() = default;

    virtual bool isWithin(const Point& position) const = 0;

    virtual std::vector<float> intersectsWithRay(const Ray& ray) const = 0;

    virtual CollisionTestResult intersects(
        const HitboxInterface& secondHitbox,
        CollectionStrategyAggregator& collectionStrategyAggregator
    ) const = 0;

    virtual std::unique_ptr<const HitboxInterface> getTransformedHitbox(const Transformation& transformation) const = 0;

    virtual CollisionTestResult intersectsWithCircle(
        const Circle& secondHitbox,
        CollectionStrategyAggregator& collectionStrategyAggregator
    ) const = 0;

    virtual CollisionTestResult intersectsWithAABB(
        const AABB& secondHitbox,
        CollectionStrategyAggregator& collectionStrategyAggregator
    ) const = 0;

    virtual CollisionTestResult intersectsWithOBB(
        const OBB& secondShape,
        CollectionStrategyAggregator& collectionStrategyAggregator
        ) const = 0;

    virtual CollisionTestResult intersectsWithTriangleAggregated(
        const Geometrics::BartaShapes::TriangleSurface& secondShape,
        CollectionStrategyAggregator& collectionStrategyAggregator
    ) const = 0;

    virtual OBB getBoundingOBB() const = 0;
};

}
