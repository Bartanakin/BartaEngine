#include <Collisions/CheckCollisionVisitors/TriangleAggregateCircle.h>
#include "Collisions/CollisionTestResult/CollisionTestResultBuilder.h"
#include "Geometrics/BartaShapes/TriangleSurface.h"

namespace Barta::Collisions::CheckCollisionVisitors {
using TriangleSurface = Geometrics::BartaShapes::TriangleSurface;

TriangleAggregateCircle::TriangleAggregateCircle(
    const TriangleSurface& triangles,
    const Circle& circle
) noexcept:
    circle(circle),
    triangles(triangles) {}

CollisionTestResult TriangleAggregateCircle::checkStaticCollision(
    const DynamicsDTOCollection& dynamicsOfFirstObject,
    const DynamicsDTOCollection& dynamicsOfSecondObject
) const {
    auto collisionTestResultBuilder = CollisionTestResultBuilder();
    collisionTestResultBuilder.setStaticCollision(true);
    collisionTestResultBuilder.setMultipleCollisions(true);

    auto C = this->circle.center;
    auto Ccur = dynamicsOfSecondObject.dynamicsDTOs[CURRENT].massCenter;
    static int counter = 0;
    for (unsigned int i = 0; i < this->triangles.triangles.size(); i++) {
        const auto& triangle = this->triangles.triangles[i];
        auto n = triangle.getNormal().normalised();
        auto X = triangle.closestPoint(C);
        auto d_square = C.squaredDistance(X);
        if (d_square > std::pow(this->circle.radius, 2)) { // No intersection - no collision
            continue;
        }

        if (n.dot(dynamicsOfSecondObject[DynamicsDTOIteration::CURRENT].velocity) > 0) { // collision detected from inwards - skip
            continue;
        }

        counter++;
        auto convexCoordinates = triangle.getConvexCoordinates(X);

        ContactPointData contactPointData;
        contactPointData.normVector = n;
        contactPointData.contactPoint = X;
        contactPointData.convexIndexFactors1 = {{0, 1.}};
        contactPointData.displacement1 = this->circle.radius * (X - C).normalised();
        contactPointData.convexIndexFactors2 = {
            {this->triangles.indices[i][0], convexCoordinates[0]},
            {this->triangles.indices[i][1], convexCoordinates[1]},
            {this->triangles.indices[i][2], convexCoordinates[2]},
        };
        contactPointData.displacement2 = {};
        collisionTestResultBuilder.addContactPointData(std::move(contactPointData));
        collisionTestResultBuilder.setCollisionDetected(true);
    }

    auto testResult = collisionTestResultBuilder.build();
    if (testResult.collisionDetected) {
        return testResult;
    }

    if (this->triangles.isWithin(circle.getCenter())) {
        // return collisionTestResultBuilder.setCollisionDetected(true)->build();
        throw std::runtime_error("Case not fully handled");
    }

    if (!this->triangles.triangles.empty() && this->circle.isWithin(this->triangles.triangles[0].p1)) {
        // return collisionTestResultBuilder.setCollisionDetected(true)->build(); // a very rare case
        throw std::runtime_error("Case not fully handled");
    }

    return collisionTestResultBuilder.build();
}

CollisionTestResult TriangleAggregateCircle::checkDynamicCollision(
    PrecisionType delta_time,
    const DynamicsDTOCollection& dynamicsOfFirstObject,
    const DynamicsDTOCollection& dynamicsOfSecondObject
) const {
    throw std::logic_error("Not implemented");
}
}
