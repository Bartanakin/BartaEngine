#pragma once
#include <Geometrics/Point.h>
#include <pch.h>

namespace Barta {

struct CollisionTestResult {
    bool collisionDetected;
    PrecisionType timePassed;
    bool staticCollision;
    Vector normVector;
    Point collisionPoint;
    std::string debugInfo;

    CollisionTestResult() noexcept:
        collisionDetected(false),
        timePassed(0.f),
        staticCollision(true),
        normVector(Vector::Zero()),
        collisionPoint(Point::Zero()) {}

    CollisionTestResult(
        bool collisionDetected,
        PrecisionType timePassed,
        bool staticCollision = false,
        Vector normVector = Vector::Zero(),
        Point collisionPoint = Point::Zero(),
        std::string debugInfo = ""
    ) noexcept:
        collisionDetected(collisionDetected),
        timePassed(timePassed),
        staticCollision(staticCollision),
        normVector(std::move(normVector)),
        collisionPoint(std::move(collisionPoint)),
        debugInfo(std::move(debugInfo)) {}

    bool operator==(
        const CollisionTestResult& second
    ) const {
        return (this->collisionDetected == second.collisionDetected) && (std::abs(this->timePassed - second.timePassed) <= 1e-6f)
               && (this->staticCollision == second.staticCollision) && (this->normVector == second.normVector);
    }
};

}
