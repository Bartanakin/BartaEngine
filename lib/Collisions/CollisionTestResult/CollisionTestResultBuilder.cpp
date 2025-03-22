#include <Collisions/CollisionTestResult/CollisionTestResultBuilder.h>

namespace Barta {
CollisionTestResultBuilder::CollisionTestResultBuilder() noexcept:
    collisionDetected(false),
    timePassed(0.f),
    staticCollision(false),
    normVector(0., 0.),
    collisionPoint(0., 0., 0.) {}

CollisionTestResult CollisionTestResultBuilder::build() const noexcept {
    std::stringstream ss;
    ss << this->debugInfo << " Objects: " << this->objectsDebugInfo << " Collision detected: " << this->collisionDetected
       << " Time passed: " << this->timePassed << " Static Collision " << this->staticCollision << " Norm vector: " << this->normVector.toString()
       << " collision point: " << this->normVector.toString();

    return {this->collisionDetected, this->timePassed, this->staticCollision, this->normVector, this->collisionPoint, ss.str()};
}

void CollisionTestResultBuilder::reset() noexcept {
    this->collisionDetected = false;
    this->timePassed = 0.f;
    this->staticCollision = false;
    this->normVector = Vector::Zero();
    this->collisionPoint = Point::Zero();
}

CollisionTestResultBuilder* CollisionTestResultBuilder::setCollisionDetected(
    bool data
) noexcept {
    this->collisionDetected = data;

    return this;
}

CollisionTestResultBuilder* CollisionTestResultBuilder::setTimePassed(
    float data
) noexcept {
    this->timePassed = data;

    return this;
}

CollisionTestResultBuilder* CollisionTestResultBuilder::setStaticCollision(
    bool data
) noexcept {
    this->staticCollision = data;

    return this;
}

CollisionTestResultBuilder* CollisionTestResultBuilder::setNormVector(
    Vector data
) noexcept {
    this->normVector = data;

    return this;
}

CollisionTestResultBuilder* CollisionTestResultBuilder::setCollisionPoint(
    Point collisionPoint
) noexcept {
    this->collisionPoint = collisionPoint;

    return this;
}

CollisionTestResultBuilder* CollisionTestResultBuilder::setDebugInfo(
    std::string data
) noexcept {
    this->debugInfo = data;

    return this;
}

CollisionTestResultBuilder* CollisionTestResultBuilder::setObjectsDebugInfo(
    std::string data
) noexcept {
    this->objectsDebugInfo = data;

    return this;
}
}
