#include <pch.h>
#include <Hitbox/HitboxComposite.h>

Barta::HitboxComposite::HitboxComposite(HitboxesList children) :
    children(std::move(children))
{}

bool Barta::HitboxComposite::isWithin(const Vector2f& position) const {
    for (const auto& child : this->children) {
        if (child->isWithin(position)) {
            return true;
        }
    }

    return false;
}

Barta::CollisionTestResult Barta::HitboxComposite::intersects(
    const HitboxInterface& secondHitbox,
    const CollisionDetectionStrategyInterface& collisionDetector,
    const DynamicsDTO& dynamicsDifference
) const {
    auto result = CollisionTestResult(false, std::numeric_limits<float>::max());
    for (auto& child : this->children) {
        auto currentResult = child->intersects(
            secondHitbox,
            collisionDetector,
            dynamicsDifference
        );

        if (currentResult.collisionDetected && currentResult.timePassed < result.timePassed) {
            result = currentResult;
        }
    }

    return result;
}

std::unique_ptr<const Barta::HitboxInterface> Barta::HitboxComposite::getTransformedHitbox(const TransformableInterface& transformable) const {
    HitboxesList result = {};
    for (auto& child : this->children) {
        result.push_back(std::move(child->getTransformedHitbox(transformable)));
    }

    return std::unique_ptr<const HitboxInterface>(new HitboxComposite(std::move(result)));
}

Barta::CollisionTestResult Barta::HitboxComposite::intersectsWithCircle(
    const Circle& secondCircle,
    const CollisionDetectionStrategyInterface& collisionDetector,
    const DynamicsDTO& dynamicsDifference
) const {
    auto result = CollisionTestResult(false, std::numeric_limits<float>::max());
    for (auto& child : this->children) {
        auto currentResult = child->intersectsWithCircle(
            secondCircle,
            collisionDetector,
            dynamicsDifference
        );

        if (currentResult.collisionDetected && currentResult.timePassed < result.timePassed) {
            result = currentResult;
        }
    }

    return result;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
Barta::CollisionTestResult Barta::HitboxComposite::intersectsWithAABB(
    const AABB& secondAABB,
    const CollisionDetectionStrategyInterface& collisionDetector,
    const DynamicsDTO& dynamicsDifference
) const {
    auto result = CollisionTestResult(false, std::numeric_limits<float>::max());
    for (auto& child : this->children) {
        auto currentResult = child->intersectsWithAABB(
            secondAABB,
            collisionDetector,
            dynamicsDifference
        );

        if (currentResult.collisionDetected && currentResult.timePassed < result.timePassed) {
            result = currentResult;
        }
    }

    return result;
}
#pragma GCC diagnostic pop