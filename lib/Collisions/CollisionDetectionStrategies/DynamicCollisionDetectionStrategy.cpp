#include "pch.h"
#include <Collisions/CollisionDetectionStrategies/DynamicCollisionDetectionStrategy.h>

Barta::DynamicCollisionDetectionStrategy::DynamicCollisionDetectionStrategy(
    std::unique_ptr<MathLibraryInterface> mathLibrary,
    const TimerInterface& timer
) :
    timer( timer ),
    mathLibrary(std::move(mathLibrary))
    {}

Barta::CollisionTestResult Barta::DynamicCollisionDetectionStrategy::acceptCheckCollisionVisitor( const CheckCollisionVisitorInterface& checkCollisionVisitor ) const{
    auto builder = CollisionTestResultBuilder();

    return checkCollisionVisitor.checkDynamicCollision(*this->mathLibrary, this->timer.getCurrentDeltaTime(), builder);
}
