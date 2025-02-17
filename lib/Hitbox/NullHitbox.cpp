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
    const CollisionDetectionStrategyInterface& collisionDetector,
    const DynamicsDifference& dynamicsDifference
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
    const CollisionDetectionStrategyInterface& collisionDetector,
    const DynamicsDifference& dynamicsDifference
) const {
    return CollisionTestResult();
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

CollisionTestResult NullHitbox::intersectsWithAABB(
    const AABB& secondAABB,
    const CollisionDetectionStrategyInterface& collisionDetector,
    const DynamicsDifference& dynamicsDifference
) const {
    return CollisionTestResult();
}

CollisionTestResult NullHitbox::intersectsWithOBB(
    const OBB& secondShape,
    const CollisionDetectionStrategyInterface& collisionDetector,
    const DynamicsDifference& dynamicsDifference
) const {
    return CollisionTestResult();
}

OBB NullHitbox::getBoundingOBB() const {
    return {{}, {}, 0.f};
}
}

#pragma GCC diagnostic pop
