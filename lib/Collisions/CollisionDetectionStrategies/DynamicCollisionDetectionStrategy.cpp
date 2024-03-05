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

    auto result = checkCollisionVisitor.checkDynamicCollision(*this->mathLibrary, this->timer.getCurrentDeltaTime(), builder);

    if (result.collisionDetected && result.debugInfo[0] != 'A') {
        std::cout << result.debugInfo << std::endl;
    }

    return result;
}
