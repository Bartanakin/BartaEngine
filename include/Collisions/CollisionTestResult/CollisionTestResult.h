#pragma once
#include "ContactPointData.h"
#include <Geometrics/Point.h>
#include <pch.h>

namespace Barta {

struct CollisionTestResult {
    bool collisionDetected;
    bool multipleCollisions;
    PrecisionType timePassed;
    bool staticCollision;
    Vector normVector;
    Point collisionPoint;
    std::vector<ContactPointData> contactPointDataArray;
    std::string debugInfo;

    CollisionTestResult() noexcept:
        collisionDetected(false),
        multipleCollisions(false),
        timePassed(0.f),
        staticCollision(true),
        normVector(Vector::Zero()),
        collisionPoint(Point::Zero()),
        contactPointDataArray({}) {}

    CollisionTestResult(
        bool collisionDetected,
        PrecisionType timePassed,
        bool multipleCollisions = false,
        bool staticCollision = false,
        Vector normVector = Vector::Zero(),
        Point collisionPoint = Point::Zero(),
        std::vector<ContactPointData> contactPointDataArray = {},
        std::string debugInfo = ""
    ) noexcept:
        collisionDetected(collisionDetected),
        multipleCollisions(multipleCollisions),
        timePassed(timePassed),
        staticCollision(staticCollision),
        normVector(std::move(normVector)),
        collisionPoint(std::move(collisionPoint)),
        contactPointDataArray(std::move(contactPointDataArray)),
        debugInfo(std::move(debugInfo)) {}

    bool operator==(
        const CollisionTestResult& second
    ) const {
        return (this->collisionDetected == second.collisionDetected) && (std::abs(this->timePassed - second.timePassed) <= 1e-6f)
               && (this->staticCollision == second.staticCollision) && (this->normVector == second.normVector);
    }

    CollisionTestResult swapObjects() {
        for (auto& contactPointData: this->contactPointDataArray) {
            std::swap(contactPointData.convexIndexFactors1, contactPointData.convexIndexFactors2);
            std::swap(contactPointData.displacement1, contactPointData.displacement2);
        }

        this->normVector = -this->normVector;

        return *this;
    }
};

}
