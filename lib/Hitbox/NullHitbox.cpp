#include <Hitbox/NullHitbox.h>
#include <Collisions/CheckCollisionVisitors/AABB_AABBCheckCollisionVisitor.h>
#include <pch.h>

namespace Barta {
bool NullHitbox::isWithin(
    const Point& position
) const {
    return false;
}

std::vector<float> NullHitbox::intersectsWithRay(
    const Ray& ray
) const {
    return {};
}

CollisionTestResult NullHitbox::intersects(
    const HitboxInterface& secondHitbox,
    CollectionStrategyAggregator& collectionStrategyAggregator
) const {
    return CollisionTestResult();
}

std::unique_ptr<const HitboxInterface> NullHitbox::getTransformedHitbox(
    const Transformation& transformation
) const {
    return std::make_unique<const NullHitbox>();
}

CollisionTestResult NullHitbox::intersectsWithCircle(
    const Circle& secondCircle,
    CollectionStrategyAggregator& collectionStrategyAggregator
) const {
    return CollisionTestResult();
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

CollisionTestResult NullHitbox::intersectsWithAABB(
    const AABB& secondAABB,
    CollectionStrategyAggregator& collectionStrategyAggregator
) const {
    return CollisionTestResult();
}

CollisionTestResult NullHitbox::intersectsWithOBB(
    const OBB& secondShape,
    CollectionStrategyAggregator& collectionStrategyAggregator
) const {
    return CollisionTestResult();
}

CollisionTestResult NullHitbox::intersectsWithTriangleAggregated(
    const Geometrics::BartaShapes::TriangleSurface& secondShape,
    CollectionStrategyAggregator& collectionStrategyAggregator
) const {
    return CollisionTestResult();
}

OBB NullHitbox::getBoundingOBB() const {
    return {{}, {}, 0.f};
}
}

#pragma GCC diagnostic pop
