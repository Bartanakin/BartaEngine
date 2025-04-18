#include <Hitbox/HitboxComposite.h>
#include <pch.h>

namespace Barta {
Barta::HitboxComposite::HitboxComposite(
    HitboxesList children
):
    children(std::move(children)) {}

bool Barta::HitboxComposite::isWithin(
    const Point& position
) const {
    for (const auto& child: this->children) {
        if (child->isWithin(position)) {
            return true;
        }
    }

    return false;
}

std::vector<float> Barta::HitboxComposite::intersectsWithRay(
    const Ray& ray
) const {
    throw std::runtime_error("Not implemented");
}

Barta::CollisionTestResult Barta::HitboxComposite::intersects(
    const HitboxInterface& secondHitbox,
    const CollisionDetectionStrategyInterface& collisionDetector,
    const DynamicsDifference& dynamicsDifference
) const {
    auto result = CollisionTestResult(false, std::numeric_limits<float>::max());
    for (auto& child: this->children) {
        auto currentResult = child->intersects(secondHitbox, collisionDetector, dynamicsDifference);

        if (currentResult.collisionDetected && currentResult.timePassed < result.timePassed) {
            result = currentResult;
        }
    }

    return result;
}

std::unique_ptr<const Barta::HitboxInterface> Barta::HitboxComposite::getTransformedHitbox(
    const Transformation& transformation
) const {
    HitboxesList result = {};
    for (auto& child: this->children) {
        result.push_back(std::move(child->getTransformedHitbox(transformation)));
    }

    return std::unique_ptr<const HitboxInterface>(new HitboxComposite(std::move(result)));
}

Barta::CollisionTestResult Barta::HitboxComposite::intersectsWithCircle(
    const Circle& secondCircle,
    const CollisionDetectionStrategyInterface& collisionDetector,
    const DynamicsDifference& dynamicsDifference
) const {
    auto result = CollisionTestResult(false, std::numeric_limits<float>::max());
    for (auto& child: this->children) {
        auto currentResult = child->intersectsWithCircle(secondCircle, collisionDetector, dynamicsDifference);

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
    const DynamicsDifference& dynamicsDifference
) const {
    auto result = CollisionTestResult(false, std::numeric_limits<float>::max());
    for (auto& child: this->children) {
        auto currentResult = child->intersectsWithAABB(secondAABB, collisionDetector, dynamicsDifference);

        if (currentResult.collisionDetected && currentResult.timePassed < result.timePassed) {
            result = currentResult;
        }
    }

    return result;
}

Barta::CollisionTestResult Barta::HitboxComposite::intersectsWithOBB(
    const OBB& secondShape,
    const CollisionDetectionStrategyInterface& collisionDetector,
    const DynamicsDifference& dynamicsDifference
) const {
    auto result = CollisionTestResult(false, std::numeric_limits<float>::max());
    for (auto& child: this->children) {
        auto currentResult = child->intersectsWithOBB(secondShape, collisionDetector, dynamicsDifference);

        if (currentResult.collisionDetected && currentResult.timePassed < result.timePassed) {
            result = currentResult;
        }
    }

    return result;
}

Barta::OBB Barta::HitboxComposite::getBoundingOBB() const {
    return {{}, {}, 0.f}; // TODO
}
}

#pragma GCC diagnostic pop
