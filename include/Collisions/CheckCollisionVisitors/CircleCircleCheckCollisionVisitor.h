#pragma once
#include "../../Dynamics/DynamicsDTO.h"
#include "../../Geometrics/BartaShapes/Circle.h"
#include "../../pch.h"
#include "../CheckCollisionVisitorInterface.h"

namespace Barta {
class CircleCircleCheckCollisionVisitor: public CheckCollisionVisitorInterface {
public:
    CircleCircleCheckCollisionVisitor(const Circle& circle1, const Circle& circle2, const DynamicsDifference& dynamicsDifference);
    virtual ~CircleCircleCheckCollisionVisitor();

    CollisionTestResult checkStaticCollision(CollisionTestResultBuilder& collisionTestResultBuilder) const override;

    CollisionTestResult checkDynamicCollision(float delta_time, CollisionTestResultBuilder& collisionTestResultBuilder) const override;

private:
    const Circle circle1;
    const Circle circle2;
    const DynamicsDifference dynamicsDifference;

    Vector2f getNormalVector() const;
};
}
