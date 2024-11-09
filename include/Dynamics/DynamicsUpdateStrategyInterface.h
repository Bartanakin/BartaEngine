#pragma once
#include "../pch.h"
#include "DynamicsAwareInterface.h"

namespace Barta {

class DynamicsUpdateStrategyInterface {
public:
    DynamicsUpdateStrategyInterface() = default;
    virtual ~DynamicsUpdateStrategyInterface() = default;

    virtual void prepare(float) = 0;

    virtual void update(bool runForward = true) = 0;
};
}
