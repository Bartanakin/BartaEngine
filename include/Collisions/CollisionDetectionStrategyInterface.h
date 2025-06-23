#pragma once
#include "../Geometrics/BartaShapes/Circle.h"
#include "../pch.h"
#include "CheckCollisionVisitorInterface.h"
#include "Dynamics/DynamicsDTOCollection.h"

namespace Barta {
class CollisionDetectionStrategyInterface {
public:
    CollisionDetectionStrategyInterface() = default;
    virtual ~CollisionDetectionStrategyInterface() = default;

    virtual CollisionTestResult acceptCheckCollisionVisitor(
        const CheckCollisionVisitorInterface& checkCollisionVisitor,
        const DynamicsDTOCollection& dynamicsOfFirstObject,
        const DynamicsDTOCollection& dynamicsOfSecondObject
    ) const = 0;
};
}
