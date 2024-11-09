#pragma once
#include "../../pch.h"
#include "CollisionTestResult.h"

namespace Barta {

class CollisionTestResultBuilder {
public:
    CollisionTestResultBuilder() noexcept;

    CollisionTestResult build() const noexcept;
    void reset() noexcept;
    CollisionTestResultBuilder* setCollisionDetected(bool data) noexcept;
    CollisionTestResultBuilder* setTimePassed(float data) noexcept;
    CollisionTestResultBuilder* setStaticCollision(bool data) noexcept;
    CollisionTestResultBuilder* setNormVector(Vector2f data) noexcept;
    CollisionTestResultBuilder* setCollisionPoint(Vector2f data) noexcept;
    CollisionTestResultBuilder* setDebugInfo(std::string data) noexcept;
    CollisionTestResultBuilder* setObjectsDebugInfo(std::string data) noexcept;

private:
    bool collisionDetected;
    float timePassed;
    bool staticCollision;
    Vector2f normVector;
    Vector2f collisionPoint;
    std::string debugInfo;
    std::string objectsDebugInfo;
};

}
