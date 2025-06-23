#include <Collisions/CheckCollisionVisitors/CircleCircleCheckCollisionVisitor.h>
#include "Collisions/CollisionTestResult/CollisionTestResultBuilder.h"
#include <Geometrics/ConvexFactor.h>
#include <Utilities/MathUtilities.h>

namespace Barta {
CircleCircleCheckCollisionVisitor::CircleCircleCheckCollisionVisitor(
    const Circle& circle1,
    const Circle& circle2
):
    circle1(circle1),
    circle2(circle2) {}

CircleCircleCheckCollisionVisitor::~CircleCircleCheckCollisionVisitor() {}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

CollisionTestResult CircleCircleCheckCollisionVisitor::checkStaticCollision(
    const DynamicsDTOCollection& dynamicsOfFirstObject,
    const DynamicsDTOCollection& dynamicsOfSecondObject
) const {
    std::stringstream ss;
    ss << "circle1: " << this->circle1 << " circle2: " << this->circle2;
    auto collisionTestResultBuilder = CollisionTestResultBuilder();

    return collisionTestResultBuilder
        .setCollisionDetected(
            static_cast<float>(pow(circle1.getRadius() + circle2.getRadius(), 2))
            >= this->circle1.getCenter().squaredDistance(this->circle2.getCenter())
        )
        ->setStaticCollision(true)
        ->setNormVector(this->getNormalVector())
        ->setCollisionPoint(ConvexFactor::convexCombination({
            {0.5f, this->circle1.getCenter()},
            {0.5f, this->circle2.getCenter()},
    }))
        ->setDebugInfo("Circle - Circle static")
        ->setObjectsDebugInfo(ss.str())
        ->build();
}

#pragma GCC diagnostic pop

CollisionTestResult CircleCircleCheckCollisionVisitor::checkDynamicCollision(
    const PrecisionType delta_time,
    const DynamicsDTOCollection& dynamicsOfFirstObject,
    const DynamicsDTOCollection& dynamicsOfSecondObject
) const {
    auto collisionTestResultBuilder = CollisionTestResultBuilder();
    auto s = circle1.getCenter() - circle2.getCenter();
    auto v = dynamicsOfFirstObject[DynamicsDTOIteration::CURRENT].velocity - dynamicsOfSecondObject[DynamicsDTOIteration::CURRENT].velocity;
    auto r = circle1.getRadius() + circle2.getRadius();

    auto eq = Utils::createQuadraticEquation(v.squaredNorm(), 2.f * v.dot(s), s.squaredNorm() - r * r);
    eq.solve();

    if (eq.getState() != Utils::EquationInterface::State::FINITE_NO_SOLTIONS) {
        return collisionTestResultBuilder.setCollisionDetected(false)->setDebugInfo("Circle - Circle dynamic, moving parallelly")->build();
    }

    auto solution = eq.getSolutions()[0];

    return collisionTestResultBuilder.setNormVector(this->getNormalVector())
        ->setCollisionDetected(0.f <= solution && solution <= delta_time)
        ->setDebugInfo("Circle - Circle dynamic")
        ->setTimePassed(solution)
        ->build();
}

Vector CircleCircleCheckCollisionVisitor::getNormalVector() const {
    return this->circle1.getCenter() - this->circle2.getCenter();
}
}
