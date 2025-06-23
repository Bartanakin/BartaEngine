#pragma once
#include <Collisions/CheckCollisionVisitorInterface.h>
#include <Dynamics/DynamicsDTO.h>
#include <Geometrics/BartaShapes/Circle.h>
#include <pch.h>

namespace Barta {
class CircleCircleCheckCollisionVisitor: public CheckCollisionVisitorInterface {
public:
    CircleCircleCheckCollisionVisitor(const Circle& circle1, const Circle& circle2);
    virtual ~CircleCircleCheckCollisionVisitor();

    CollisionTestResult checkStaticCollision(const DynamicsDTOCollection& dynamicsOfFirstObject, const DynamicsDTOCollection& dynamicsOfSecondObject)
        const override;

    CollisionTestResult checkDynamicCollision(
        PrecisionType delta_time,
        const DynamicsDTOCollection& dynamicsOfFirstObject,
        const DynamicsDTOCollection& dynamicsOfSecondObject
    ) const override;

private:
    const Circle circle1;
    const Circle circle2;

    Vector getNormalVector() const;
};
}
