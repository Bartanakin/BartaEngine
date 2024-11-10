#pragma once

#include "../../pch.h"
#include "../CollisionDetectionStrategyInterface.h"
#include <Collisions/CollisionTestResult/CollisionTestResult.h>

namespace Barta {
class StaticCollisionDetectionStrategy: public CollisionDetectionStrategyInterface {
public:
    StaticCollisionDetectionStrategy();
    virtual ~StaticCollisionDetectionStrategy() noexcept = default;

    virtual CollisionTestResult acceptCheckCollisionVisitor(const CheckCollisionVisitorInterface& checkCollisionVisitor) const override;
};
}
