#pragma once
#include "Collisions/CollisionDetectionStrategyInterface.h"
#include <pch.h>

namespace Barta::Collisions::CollisionDetectionStrategies {
class CollectionStrategyAggregator {
public:
    CollectionStrategyAggregator(
        CollisionDetectionStrategyInterface& collisionDetectionStrategy,
        DynamicsDTOCollection dynamics1,
        DynamicsDTOCollection dynamics2
    ) noexcept;

    CollectionStrategyAggregator swapObjects() noexcept;

    CollisionTestResult acceptCheckCollisionVisitor(const CheckCollisionVisitorInterface& checkCollisionVisitor) const;

    CollectionStrategyAggregator applyTransform(const Matrix& transformation);

private:
    CollectionStrategyAggregator(
        CollisionDetectionStrategyInterface& collisionDetectionStrategy,
        std::array<DynamicsDTOCollection, 2> dynamicsCollections,
        std::array<unsigned int, 2> dynamicsCollectionIndices
    ) noexcept;

    CollisionDetectionStrategyInterface& collisionDetectionStrategy;
    std::array<DynamicsDTOCollection, 2> dynamicsCollections;
    std::array<unsigned int, 2> dynamicsCollectionIndices;
};
}
