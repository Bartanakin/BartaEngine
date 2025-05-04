//
// Created by bartanakin on 10/27/24.
//

#include <Collisions/CheckCollisionVisitors/OBB_AABBCheckCollisionVisitor.h>
#include <Geometrics/ConvexFactor.h>

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
        auto projection = vertex.x();
        if (projection < min) {
            min = projection;
        }

        if (projection > max) {
            max = projection;
        }
    }

    if (aabb.getLeftTop().x() > max || (aabb.getWidthHeight() + aabb.getLeftTop()).x() < min) {
        return true;
    }

    min = std::numeric_limits<float>::max();
    max = -std::numeric_limits<float>::max();
    for (auto& vertex: obb.getVertices()) {
        auto projection = vertex.y();
        if (projection < min) {
            min = projection;
        }

        if (projection > max) {
            max = projection;
        }
    }

    if (aabb.getLeftTop().y() > max || (aabb.getWidthHeight() + aabb.getLeftTop()).y() < min) {
        return true;
    }

    return false;
}

Barta::CollisionTestResult Barta::OBB_AABBCheckCollisionVisitor::checkStaticCollision(
    CollisionTestResultBuilder& collisionTestResultBuilder
) const {
    std::stringstream ss;
    ss << "obb " << this->obb << " aabb: " << this->obb << " velocity: " << this->dynamicsDifference.velocity;
    collisionTestResultBuilder.setStaticCollision(true)->setDebugInfo("OOB - AABB static")->setObjectsDebugInfo(ss.str());

    Matrix M = Transformation::translation(-this->aabb.getLeftTop().toVector()) * this->obb.getTransformation().getMatrix();
    auto relativeAabb = AABB(Point::Zero(), this->aabb.getWidthHeight());
    auto relativeObb = OBB(this->obb.getWidthHeight(), Transformation(M));
    if (OBB_AABBCheckCollisionVisitor::checkStaticOneWay(relativeAabb, relativeObb)) {
        return collisionTestResultBuilder.build();
    }

    M = this->obb.getTransformation().getMatrix().inverse();
    auto relativeObb2 = OBB(this->aabb.getWidthHeight(), Transformation(M));
    auto relativeAabb2 = AABB(Point::Zero(), this->obb.getWidthHeight());
    if (OBB_AABBCheckCollisionVisitor::checkStaticOneWay(relativeAabb2, relativeObb2)) {
        return collisionTestResultBuilder.build();
    }

    return collisionTestResultBuilder.setCollisionDetected(true)->setCollisionPoint(this->calculateCollisionPoint())->build();
}

Barta::CollisionTestResult Barta::OBB_AABBCheckCollisionVisitor::checkDynamicCollision(
    PrecisionType deltaTime,
    CollisionTestResultBuilder& collisionTestResultBuilder
) const {
    // throw std::runtime_error("Not implemented");
    return collisionTestResultBuilder.build();
}

Barta::Point Barta::OBB_AABBCheckCollisionVisitor::calculateCollisionPoint() const {
    AABB::PointDistance maxDistance;
    Point collisionPoint{};
    maxDistance.distance = std::numeric_limits<float>::max();
    for (const auto p: this->aabb.getVertices()) {
        auto closest = this->obb.closestPointTo(p);
        if (closest.distance < maxDistance.distance) {
            maxDistance = closest;
            collisionPoint = ConvexFactor::convexCombination({
                {0.5, p            },
                {0.5, closest.point}
            });
        }
    }

    for (const auto p: this->obb.getVertices()) {
        auto closest = this->aabb.closestPointTo(p);
        if (closest.distance < maxDistance.distance) {
            maxDistance = closest;
            collisionPoint = ConvexFactor::convexCombination({
                {0.5, p            },
                {0.5, closest.point}
            });
        }
    }

    return collisionPoint;
}
