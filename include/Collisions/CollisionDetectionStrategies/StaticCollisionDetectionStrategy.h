#pragma once

#include "../../pch.h"
#include "../CollisionDetectionStrategyInterface.h"
#include <Collisions/CollisionTestResult/CollisionTestResult.h>

namespace Barta {
class StaticCollisionDetectionStrategy: public CollisionDetectionStrategyInterface {
public:
    StaticCollisionDetectionStrategy();
    virtual ~StaticCollisionDetectionStrategy() noexcept = default;

    CollisionTestResult acceptCheckCollisionVisitor(
        const CheckCollisionVisitorInterface& checkCollisionVisitor,
        const DynamicsDTOCollection& dynamicsOfFirstObject,
        const DynamicsDTOCollection& dynamicsOfSecondObject
    ) const override;
};
}
