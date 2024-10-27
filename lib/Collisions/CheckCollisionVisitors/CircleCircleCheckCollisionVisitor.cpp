#include <Collisions/CheckCollisionVisitors/CircleCircleCheckCollisionVisitor.h>
#include "pch.h"

Barta::CircleCircleCheckCollisionVisitor::CircleCircleCheckCollisionVisitor(
    const Circle& circle1,
    const Circle& circle2,
    const DynamicsDifference& dynamicsDifference
):
    circle1(circle1),
    circle2(circle2),
    dynamicsDifference(dynamicsDifference) {}

Barta::CircleCircleCheckCollisionVisitor::~CircleCircleCheckCollisionVisitor() {}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

Barta::CollisionTestResult Barta::CircleCircleCheckCollisionVisitor::checkStaticCollision(
    const MathLibraryInterface& mathLib,
    CollisionTestResultBuilder& collisionTestResultBuilder
) const {
    std::stringstream ss;
    ss << "circle1: " << this->circle1 << " circle2: " << this->circle2 << " velocity: " << this->dynamicsDifference.velocity;

    return collisionTestResultBuilder
        .setCollisionDetected(
            static_cast<float>(pow(circle1.getRadius() + circle2.getRadius(), 2))
            >= this->circle1.getCenter().squareOfDistance(this->circle2.getCenter())
        )
        ->setStaticCollision(true)
        ->setDebugInfo("Circle - Circle static")
        ->setObjectsDebugInfo(ss.str())
        ->build();
}

#pragma GCC diagnostic pop

Barta::CollisionTestResult Barta::CircleCircleCheckCollisionVisitor::checkDynamicCollision(
    const MathLibraryInterface& mathLib,
    const float delta_time,
    CollisionTestResultBuilder& collisionTestResultBuilder
) const {
    auto staticResult = this->checkStaticCollision(mathLib, collisionTestResultBuilder);
    if (staticResult.collisionDetected) {
        return staticResult;
    }

    collisionTestResultBuilder.reset();
    auto s = circle1.getCenter() - circle2.getCenter();
    auto v = dynamicsDifference.velocity + 0.5f * dynamicsDifference.acceleration * delta_time;
    auto r = circle1.getRadius() + circle2.getRadius();

    auto eq = mathLib.createQuadraticEquation(v * v, v * s * 2.f, s * s - r * r);
    eq->solve();

    if (eq->getState() != EquationInterface::State::FINITE_NO_SOLTIONS) {
        return collisionTestResultBuilder.setCollisionDetected(false)->setDebugInfo("Circle - Circle dynamic, moving parallelly")->build();
    }

    auto solution = eq->getSolutions()[0];

    return collisionTestResultBuilder.setNormVector(this->getNormalVector())
        ->setCollisionDetected(0.f <= solution && solution <= delta_time)
        ->setDebugInfo("Circle - Circle dynamic")
        ->setTimePassed(solution)
        ->build();
}

Barta::Vector2f Barta::CircleCircleCheckCollisionVisitor::getNormalVector() const {
    return this->circle1.getCenter() - this->circle2.getCenter();
}
