#pragma once
#include "../../Dynamics/TimerInterface.h"
#include "../../pch.h"
#include "../CollisionDetectionStrategyInterface.h"

namespace Barta {
class DynamicCollisionDetectionStrategy: public CollisionDetectionStrategyInterface {
public:
    DynamicCollisionDetectionStrategy(const TimerInterface& timer);
    virtual ~DynamicCollisionDetectionStrategy() noexcept = default;

     CollisionTestResult acceptCheckCollisionVisitor(
        const CheckCollisionVisitorInterface& checkCollisionVisitor,
        const DynamicsDTOCollection& dynamicsOfFirstObject,
        const DynamicsDTOCollection& dynamicsOfSecondObject
    ) const override;

private:
    const TimerInterface& timer;
};
}
