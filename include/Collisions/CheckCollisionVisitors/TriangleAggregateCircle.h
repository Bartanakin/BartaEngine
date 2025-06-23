#pragma once
#include "Collisions/CheckCollisionVisitorInterface.h"
#include "Geometrics/BartaShapes/Circle.h"
#include "Geometrics/BartaShapes/TriangleSurface.h"
#include <pch.h>

namespace Barta::Collisions::CheckCollisionVisitors {
class TriangleAggregateCircle: public CheckCollisionVisitorInterface {
public:
    TriangleAggregateCircle(const Geometrics::BartaShapes::TriangleSurface& triangles, const Circle& circle) noexcept;

    CollisionTestResult checkStaticCollision(const DynamicsDTOCollection& dynamicsOfFirstObject, const DynamicsDTOCollection& dynamicsOfSecondObject)
        const override;

    CollisionTestResult checkDynamicCollision(
        PrecisionType delta_time,
        const DynamicsDTOCollection& dynamicsOfFirstObject,
        const DynamicsDTOCollection& dynamicsOfSecondObject
    ) const override;

private:
    const Geometrics::BartaShapes::TriangleSurface& triangles;
    const Circle& circle;
};
}
