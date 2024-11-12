#pragma once
#include "../../Dynamics/TimerInterface.h"
#include "../../pch.h"
#include "../CollisionDetectionStrategyInterface.h"

namespace Barta {
class DynamicCollisionDetectionStrategy: public CollisionDetectionStrategyInterface {
public:
    DynamicCollisionDetectionStrategy(const TimerInterface& timer);
    virtual ~DynamicCollisionDetectionStrategy() noexcept = default;

    virtual CollisionTestResult acceptCheckCollisionVisitor(const CheckCollisionVisitorInterface& checkCollisionVisitor) const override;

private:
    const TimerInterface& timer;
};
}
