#pragma once
#include "Geometrics/BartaShapes/Triangle.h"
#include "HitboxInterface.h"
#include <pch.h>

namespace Barta::Hitbox {
class TriangleAggregateHitbox: public HitboxInterface {
public:
    TriangleAggregateHitbox(
        Geometrics::BartaShapes::TriangleSurface triangles
    ) noexcept:
        triangles(std::move(triangles)) {}

    bool isWithin(const Point& position) const override;

    std::vector<float> intersectsWithRay(const Ray& ray) const override;

    CollisionTestResult intersects(
        const HitboxInterface& secondHitbox,
        CollectionStrategyAggregator& collectionStrategyAggregator
    ) const override;

    std::unique_ptr<const HitboxInterface> getTransformedHitbox(const Transformation& transformation) const override;

    CollisionTestResult intersectsWithCircle(
        const Circle& circle,
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

    OBB getBoundingOBB() const override;

private:
    // An enclosed mesh of triangles where all normals point outwards. It does not have to be convex.
    Geometrics::BartaShapes::TriangleSurface triangles;
};
}
