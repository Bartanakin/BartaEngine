#include <Hitbox/NullHitbox.h>
#include <Collisions/CheckCollisionVisitors/AABB_AABBCheckCollisionVisitor.h>
#include <pch.h>

bool Barta::NullHitbox::isWithin(
    const Vector2f& position
) const {
    return false;
}

Barta::CollisionTestResult Barta::NullHitbox::intersects(
    const HitboxInterface& secondHitbox,
    const CollisionDetectionStrategyInterface& collisionDetector,
    const DynamicsDifference& dynamicsDifference
) const {
    return CollisionTestResult();
}

std::unique_ptr<const Barta::HitboxInterface> Barta::NullHitbox::getTransformedHitbox(
    const TransformableInterface& transformable
) const {
    return std::unique_ptr<const HitboxInterface>(new NullHitbox());
}

Barta::CollisionTestResult Barta::NullHitbox::intersectsWithCircle(
    const Circle& secondCircle,
    const CollisionDetectionStrategyInterface& collisionDetector,
    const DynamicsDifference& dynamicsDifference
) const {
    return CollisionTestResult();
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

Barta::CollisionTestResult Barta::NullHitbox::intersectsWithAABB(
    const AABB& secondAABB,
    const CollisionDetectionStrategyInterface& collisionDetector,
    const DynamicsDifference& dynamicsDifference
) const {
    return CollisionTestResult();
}

Barta::CollisionTestResult Barta::NullHitbox::intersectsWithOBB(
    const OBB& secondShape,
    const CollisionDetectionStrategyInterface& collisionDetector,
    const DynamicsDifference& dynamicsDifference
) const {
    return CollisionTestResult();
}

#pragma GCC diagnostic pop
