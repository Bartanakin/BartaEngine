#include <Collisions/CollisionDetectionStrategies/CollectionStrategyAggregator.h>

namespace Barta::Collisions::CollisionDetectionStrategies {
CollectionStrategyAggregator::CollectionStrategyAggregator(
    CollisionDetectionStrategyInterface& collisionDetectionStrategy,
    DynamicsDTOCollection dynamics1,
    DynamicsDTOCollection dynamics2
) noexcept:
    collisionDetectionStrategy(collisionDetectionStrategy),
    dynamicsCollections({dynamics1, dynamics2}),
    dynamicsCollectionIndices({0, 1}) {}

CollectionStrategyAggregator CollectionStrategyAggregator::swapObjects() noexcept {
    std::swap(dynamicsCollectionIndices[0], dynamicsCollectionIndices[1]);

    return *this;
}

CollisionTestResult CollectionStrategyAggregator::acceptCheckCollisionVisitor(
    const CheckCollisionVisitorInterface& checkCollisionVisitor
) const {
    return this->collisionDetectionStrategy.acceptCheckCollisionVisitor(
        checkCollisionVisitor,
        this->dynamicsCollections[dynamicsCollectionIndices[0]],
        this->dynamicsCollections[dynamicsCollectionIndices[1]]
    );
}

CollectionStrategyAggregator CollectionStrategyAggregator::applyTransform(
    const Matrix& transformation
) {
    for (auto& dynamicsCollection: this->dynamicsCollections) {
        for (auto& dynamics: dynamicsCollection.dynamicsDTOs) {
            dynamics = transformation * dynamics;
        }
    }

    return *this;
}

CollectionStrategyAggregator::CollectionStrategyAggregator(
    CollisionDetectionStrategyInterface& collisionDetectionStrategy,
    std::array<DynamicsDTOCollection, 2> dynamicsCollections,
    std::array<unsigned int, 2> dynamicsCollectionIndices
) noexcept:
    collisionDetectionStrategy(collisionDetectionStrategy),
    dynamicsCollections(dynamicsCollections),
    dynamicsCollectionIndices(dynamicsCollectionIndices) {}
}
