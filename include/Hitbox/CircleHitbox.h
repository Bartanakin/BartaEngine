#pragma once
#include "Geometrics/BartaShapes/TriangleSurface.h"
#include <Geometrics/BartaShapes/OBB.h>
#include <Geometrics/Transformation.h>
#include <Hitbox/HitboxInterface.h>

namespace Barta {

class CircleHitbox final: public HitboxInterface {
public:
    CircleHitbox(const Circle& circle);
    ~CircleHitbox() = default;

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

private:
    const Circle& getCircle() const;

    Circle circle;
};

}
