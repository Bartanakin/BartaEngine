#include <Collisions/CollisionTestResult/CollisionTestResultBuilder.h>
#include "pch.h"

Barta::CollisionTestResultBuilder::CollisionTestResultBuilder() noexcept:
    collisionDetected(false),
    timePassed(0.f),
    staticCollision(false),
    normVector(0., 0.),
    collisionPoint(0., 0.),
    debugInfo(""),
    objectsDebugInfo("") {}

Barta::CollisionTestResult Barta::CollisionTestResultBuilder::build() const noexcept {
    std::stringstream ss;
    ss << this->debugInfo << " Objects: " << this->objectsDebugInfo << " Collision detected: " << this->collisionDetected
       << " Time passed: " << this->timePassed << " Static Collision " << this->staticCollision << " Norm vector: " << this->normVector
       << " collision point: " << this->normVector;

    return CollisionTestResult(this->collisionDetected, this->timePassed, this->staticCollision, this->normVector, this->collisionPoint, ss.str());
}

void Barta::CollisionTestResultBuilder::reset() noexcept {
    this->collisionDetected = false;
    this->timePassed = 0.f;
    this->staticCollision = false;
    this->normVector = Vector2f(0., 0.);
    this->collisionPoint = Vector2f(0., 0.);
}

Barta::CollisionTestResultBuilder* Barta::CollisionTestResultBuilder::setCollisionDetected(
    bool data
) noexcept {
    this->collisionDetected = data;

    return this;
}

Barta::CollisionTestResultBuilder* Barta::CollisionTestResultBuilder::setTimePassed(
    float data
) noexcept {
    this->timePassed = data;

    return this;
}

Barta::CollisionTestResultBuilder* Barta::CollisionTestResultBuilder::setStaticCollision(
    bool data
) noexcept {
    this->staticCollision = data;

    return this;
}

Barta::CollisionTestResultBuilder* Barta::CollisionTestResultBuilder::setNormVector(
    Barta::Vector2f data
) noexcept {
    this->normVector = data;

    return this;
}

Barta::CollisionTestResultBuilder* Barta::CollisionTestResultBuilder::setCollisionPoint(
    Vector2f collisionPoint
) noexcept {
    this->collisionPoint = collisionPoint;

    return this;
}

Barta::CollisionTestResultBuilder* Barta::CollisionTestResultBuilder::setDebugInfo(
    std::string data
) noexcept {
    this->debugInfo = data;

    return this;
}

Barta::CollisionTestResultBuilder* Barta::CollisionTestResultBuilder::setObjectsDebugInfo(
    std::string data
) noexcept {
    this->objectsDebugInfo = data;

    return this;
}
