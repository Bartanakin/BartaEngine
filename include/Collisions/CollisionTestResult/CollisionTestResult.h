#pragma once
#include "../../Geometrics/Vector2f.h"
#include "../../pch.h"

namespace Barta {

struct CollisionTestResult {
    bool collisionDetected;
    float timePassed;
    bool staticCollision;
    Vector2f normVector;
    Vector2f collisionPoint;
    std::string debugInfo;

    CollisionTestResult() noexcept:
        collisionDetected(false),
        timePassed(0.f),
        staticCollision(true),
        normVector(Vector2f()),
        collisionPoint(Vector2f()),
        debugInfo("") {}

    CollisionTestResult(
        bool collisionDetected,
        float timePassed,
        bool staticCollision = false,
        Vector2f normVector = {},
        Vector2f collisionPoint = {},
        std::string debugInfo = ""
    ) noexcept:
        collisionDetected(collisionDetected),
        timePassed(timePassed),
        staticCollision(staticCollision),
        normVector(normVector),
        collisionPoint(collisionPoint),
        debugInfo(debugInfo) {}

    bool operator==(
        const CollisionTestResult& second
    ) const {
        return (this->collisionDetected == second.collisionDetected) && (std::abs(this->timePassed - second.timePassed) <= 1e-6f)
               && (this->staticCollision == second.staticCollision) && (this->normVector == second.normVector);
    }
};

}
