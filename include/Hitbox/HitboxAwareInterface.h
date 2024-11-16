#pragma once
#include "../Geometrics/TransformableInterface.h"
#include "../pch.h"
#include "HitboxAwareConcept.h"
#include "HitboxInterface.h"

namespace Barta {

class HitboxAware {
public:
    HitboxAware() = default;
    virtual ~HitboxAware() = default;

    virtual std::unique_ptr<const HitboxInterface> getHitbox() const = 0;
};

static_assert(HitboxAwareConcept<HitboxAware>);
}
