#include <Collisions/CheckCollisionVisitors/AABB_AABBCheckCollisionVisitor.h>
#include <Geometrics/ConvexFactor.h>

namespace Barta {
AABB_AABBCheckCollisionVisitor::AABB_AABBCheckCollisionVisitor(
    const AABB& aabb1,
    const AABB& aabb2,
    const DynamicsDifference& dynamicsDifference
) noexcept:
    aabb1(aabb1),
    aabb2(aabb2),
    dynamicsDifference(dynamicsDifference) {}

CollisionTestResult AABB_AABBCheckCollisionVisitor::checkStaticCollision(
    CollisionTestResultBuilder& collisionTestResultBuilder
) const {
    std::stringstream ss;
    ss << "aabb1 " << this->aabb1 << " aabb2: " << this->aabb2 << " velocity: " << this->dynamicsDifference.velocity;

    return collisionTestResultBuilder
        .setCollisionDetected(
            this->aabb1.getLeftTop().x() <= this->aabb2.getRightTop().x() && this->aabb1.getRightTop().x() >= this->aabb2.getLeftTop().x()
            && this->aabb1.getLeftTop().y() <= this->aabb2.getLeftBottom().y() && this->aabb1.getLeftBottom().y() >= this->aabb2.getLeftTop().y()
        )
        ->setCollisionPoint(this->calculateCollisionPoint())
        ->setStaticCollision(true)
        ->setDebugInfo("AABB - AABB static")
        ->setObjectsDebugInfo(ss.str())
        ->build();
}

CollisionTestResult AABB_AABBCheckCollisionVisitor::checkDynamicCollision(
    const float delta_time,
    CollisionTestResultBuilder& collisionTestResultBuilder
) const {
    auto staticCollisionResult = this->checkStaticCollision(collisionTestResultBuilder);
    if (staticCollisionResult.collisionDetected) {
        return staticCollisionResult;
    }

    collisionTestResultBuilder.setStaticCollision(false)->setCollisionDetected(false);
    if (this->dynamicsDifference.velocity == Vector::Zero()) {
        return collisionTestResultBuilder.setDebugInfo("AABB - AABB zero velocity")->build();
    }

    float t_first = 0.f;
    float t_last = delta_time;
    Vector normVector = {};
    std::vector<std::tuple<const float, const float, const float, const float, const float, const Vector, std::string>> dataVector = {
        {this->dynamicsDifference.velocity.x(),
         this->aabb2.getLeftTop().x(),
         this->aabb2.getRightTop().x(),
         this->aabb1.getLeftTop().x(),
         this->aabb1.getRightTop().x(),
         Vector(1.f, 0.f),
         "x"},
        {this->dynamicsDifference.velocity.y(),
         this->aabb2.getLeftTop().y(),
         this->aabb2.getLeftBottom().y(),
         this->aabb1.getLeftTop().y(),
         this->aabb1.getLeftBottom().y(),
         Vector(0.f, 1.f),
         "y"}
    };
    static constexpr const int VELOCITY = 0;
    static constexpr const int MIN_1 = 1;
    static constexpr const int MAX_1 = 2;
    static constexpr const int MIN_2 = 3;
    static constexpr const int MAX_2 = 4;
    static constexpr const int NORM_VECTOR = 5;
    static constexpr const int AXIS = 6;
    for (const auto& data: dataVector) {
        if (std::get<VELOCITY>(data) < 0.f) {
            if (std::get<MAX_2>(data) < std::get<MIN_1>(data)) {
                return collisionTestResultBuilder.setDebugInfo("AABB - AABB dynamic, velocity in the opposite direction (negative)")->build();
            }

            if (std::get<MAX_1>(data) < std::get<MIN_2>(data)) {
                t_first = std::max((std::get<MAX_1>(data) - std::get<MIN_2>(data)) / std::get<VELOCITY>(data), t_first);
                normVector = std::get<NORM_VECTOR>(data);
            }

            t_last = std::min((std::get<MIN_1>(data) - std::get<MAX_2>(data)) / std::get<VELOCITY>(data), t_last);
        }

        if (std::get<VELOCITY>(data) > 0.f) {
            if (std::get<MIN_2>(data) > std::get<MAX_1>(data)) {
                return collisionTestResultBuilder
                    .setDebugInfo("AABB - AABB dynamic, velocity in the opposite direction (positive)" + std::get<AXIS>(data))
                    ->build();
            }

            if (std::get<MAX_2>(data) < std::get<MIN_1>(data)) {
                t_first = std::max((std::get<MIN_1>(data) - std::get<MAX_2>(data)) / std::get<VELOCITY>(data), t_first);
                normVector = -std::get<NORM_VECTOR>(data);
            }

            t_last = std::min((std::get<MAX_1>(data) - std::get<MIN_2>(data)) / std::get<VELOCITY>(data), t_last);
        }

        if (std::get<VELOCITY>(data) == 0.f) {
            if (std::get<MIN_2>(data) > std::get<MAX_1>(data) || std::get<MIN_1>(data) > std::get<MAX_2>(data)) {
                return collisionTestResultBuilder
                    .setDebugInfo("AABB - AABB dynamic, velocity in the opposite direction (positive)" + std::get<AXIS>(data))
                    ->build();
            }
        }

        if (t_first > t_last) {
            return collisionTestResultBuilder.setDebugInfo("AABB - AABB dynamic, 0 velocity in axis" + std::get<AXIS>(data))->build();
        }
    }

    return collisionTestResultBuilder.setCollisionDetected(true)
        ->setTimePassed(t_first)
        ->setNormVector(normVector)
        ->setDebugInfo("AABB - AABB succesful dynamic")
        ->build();
}

Point AABB_AABBCheckCollisionVisitor::calculateCollisionPoint() const {
    AABB::PointDistance maxDistance;
    Point collisionPoint{};
    maxDistance.distance = std::numeric_limits<float>::min();
    for (const auto p: this->aabb1.getVertices()) {
        auto closest = this->aabb2.closestPointTo(p);
        if (closest.distance < maxDistance.distance) {
            maxDistance = closest;
            collisionPoint = ConvexFactor::convexCombination({
                {0.5f, p            },
                {0.5f, closest.point},
            });
        }
    }

    for (const auto p: this->aabb2.getVertices()) {
        auto closest = this->aabb1.closestPointTo(p);
        if (closest.distance < maxDistance.distance) {
            maxDistance = closest;
            collisionPoint = ConvexFactor::convexCombination({
                {0.5f, p            },
                {0.5f, closest.point},
            });
        }
    }

    return collisionPoint;
}
}
