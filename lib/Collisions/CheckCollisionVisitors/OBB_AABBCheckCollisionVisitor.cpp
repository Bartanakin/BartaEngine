//
// Created by bartanakin on 10/27/24.
//

#include <Collisions/CheckCollisionVisitors/OBB_AABBCheckCollisionVisitor.h>

Barta::OBB_AABBCheckCollisionVisitor::OBB_AABBCheckCollisionVisitor(
    const OBB& obb,
    const AABB& aabb,
    const DynamicsDifference& dynamicsDifference
) noexcept:
    obb(obb),
    aabb(aabb),
    dynamicsDifference(dynamicsDifference) {}

bool Barta::OBB_AABBCheckCollisionVisitor::checkStaticOneWay(
    const AABB& aabb,
    const OBB& obb
) {
    auto min = std::numeric_limits<float>::max();
    auto max = -std::numeric_limits<float>::max();
    for (auto& vertex: obb.getVertices()) {
        auto projection = vertex.x;
        if (projection < min) {
            min = projection;
        }

        if (projection > max) {
            max = projection;
        }
    }

    if (aabb.getLeftTop().x > max || (aabb.getWidthHeight() + aabb.getLeftTop()).x < min) {
        return true;
    }

    min = std::numeric_limits<float>::max();
    max = -std::numeric_limits<float>::max();
    for (auto& vertex: obb.getVertices()) {
        auto projection = vertex.y;
        if (projection < min) {
            min = projection;
        }

        if (projection > max) {
            max = projection;
        }
    }

    if (aabb.getLeftTop().y > max || (aabb.getWidthHeight() + aabb.getLeftTop()).y < min) {
        return true;
    }

    return false;
}

Barta::CollisionTestResult Barta::OBB_AABBCheckCollisionVisitor::checkStaticCollision(
    const MathLibraryInterface& mathLib,
    CollisionTestResultBuilder& collisionTestResultBuilder
) const {
    std::stringstream ss;
    ss << "obb " << this->obb << " aabb: " << this->obb << " velocity: " << this->dynamicsDifference.velocity;
    collisionTestResultBuilder.setStaticCollision(true)->setDebugInfo("OOB - AABB static")->setObjectsDebugInfo(ss.str());
    auto relativeAabb = AABB({}, this->aabb.getWidthHeight());
    auto relativeObb = OBB(this->obb.getFirstVertex() - this->aabb.getLeftTop(), this->obb.getWidthHeight(), this->obb.getRotation());
    if (OBB_AABBCheckCollisionVisitor::checkStaticOneWay(relativeAabb, relativeObb)) {
        return collisionTestResultBuilder.build();
    }

    auto relativeAabb2 = AABB({}, this->obb.getWidthHeight());
    auto relativeObb2 =
        OBB((this->aabb.getLeftTop() - this->obb.getFirstVertex()).rotated(-this->obb.getRotation()),
            this->aabb.getWidthHeight(),
            -this->obb.getRotation());
    if (OBB_AABBCheckCollisionVisitor::checkStaticOneWay(relativeAabb2, relativeObb2)) {
        return collisionTestResultBuilder.build();
    }

    return collisionTestResultBuilder.setCollisionDetected(true)->build();
}

Barta::CollisionTestResult Barta::OBB_AABBCheckCollisionVisitor::checkDynamicCollision(
    const MathLibraryInterface& mathLib,
    float deltaTime,
    CollisionTestResultBuilder& collisionTestResultBuilder
) const {
    throw std::runtime_error("Not implemented");
}
