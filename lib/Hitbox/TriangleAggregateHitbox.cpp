#include <Hitbox/TriangleAggregateHitbox.h>
#include "Collisions/CheckCollisionVisitors/TriangleAggregateCircle.h"
#include "Geometrics/Intersections.h"

namespace Barta::Hitbox {
bool TriangleAggregateHitbox::isWithin(
    const Point& position
) const {
    return this->triangles.isWithin(position);
}

std::vector<float> TriangleAggregateHitbox::intersectsWithRay(
    const Ray& ray
) const {
    return this->triangles.intersectsWithRay(ray);
}

CollisionTestResult TriangleAggregateHitbox::intersects(
    const HitboxInterface& secondHitbox,
    CollectionStrategyAggregator& collectionStrategyAggregator
) const {
    return secondHitbox.intersectsWithTriangleAggregated(this->triangles, collectionStrategyAggregator);
}

std::unique_ptr<const HitboxInterface> TriangleAggregateHitbox::getTransformedHitbox(
    const Transformation& transformation
) const {
    throw std::runtime_error("Not implemented");
}

CollisionTestResult TriangleAggregateHitbox::intersectsWithCircle(
    const Circle& circle,
    CollectionStrategyAggregator& collectionStrategyAggregator
) const {
    return collectionStrategyAggregator.swapObjects().acceptCheckCollisionVisitor(
        Collisions::CheckCollisionVisitors::TriangleAggregateCircle(this->triangles, circle)
    );
}

CollisionTestResult TriangleAggregateHitbox::intersectsWithAABB(
    const AABB& secondHitbox,
    CollectionStrategyAggregator& collectionStrategyAggregator
) const {
    throw std::runtime_error("Not implemented");
}

CollisionTestResult TriangleAggregateHitbox::intersectsWithOBB(
    const OBB& secondShape,
    CollectionStrategyAggregator& collectionStrategyAggregator
) const {
    throw std::runtime_error("Not implemented");
}

CollisionTestResult TriangleAggregateHitbox::intersectsWithTriangleAggregated(
    const Geometrics::BartaShapes::TriangleSurface& secondShape,
    CollectionStrategyAggregator& collectionStrategyAggregator
) const {
    throw std::runtime_error("Not implemented");
}

OBB TriangleAggregateHitbox::getBoundingOBB() const {
    Point maxPoint = {-std::numeric_limits<float>::max(), -std::numeric_limits<float>::max(), -std::numeric_limits<float>::max()};
    Point minPoint = {std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};
    for (const auto& triangle: this->triangles.triangles) {
        for (const auto& vertex: {triangle.p1, triangle.p2, triangle.p3}) {
            for (auto& [minCord, cord]: std::vector<std::pair<PrecisionType&, PrecisionType>>{
                     {minPoint.x(), vertex.x()},
                     {minPoint.y(), vertex.y()},
                     {minPoint.z(), vertex.z()}
            }) {
                if (cord < minCord) {
                    minCord = cord;
                }
            }

            for (auto& [maxCord, cord]: std::vector<std::pair<PrecisionType&, PrecisionType>>{
                     {maxPoint.x(), vertex.x()},
                     {maxPoint.y(), vertex.y()},
                     {maxPoint.z(), vertex.z()}
            }) {
                if (cord > maxCord) {
                    maxCord = cord;
                }
            }
        }
    }

    return {minPoint, maxPoint - minPoint, 0.};
}
}
