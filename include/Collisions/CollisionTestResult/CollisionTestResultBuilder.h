#pragma once
#include <Collisions/CollisionTestResult/CollisionTestResult.h>
#include <Geometrics/Point.h>
#include <pch.h>

namespace Barta {

class CollisionTestResultBuilder {
public:
    CollisionTestResultBuilder() noexcept;

    CollisionTestResult build() const noexcept;
    void reset() noexcept;
    CollisionTestResultBuilder* setCollisionDetected(bool data) noexcept;
    CollisionTestResultBuilder* setTimePassed(float data) noexcept;
    CollisionTestResultBuilder* setStaticCollision(bool data) noexcept;
    CollisionTestResultBuilder* setNormVector(Vector data) noexcept;
    CollisionTestResultBuilder* setCollisionPoint(Point data) noexcept;
    CollisionTestResultBuilder* setDebugInfo(std::string data) noexcept;
    CollisionTestResultBuilder* setObjectsDebugInfo(std::string data) noexcept;

private:
    bool collisionDetected;
    float timePassed;
    bool staticCollision;
    Vector normVector;
    Point collisionPoint;
    std::string debugInfo;
    std::string objectsDebugInfo;
};

}
