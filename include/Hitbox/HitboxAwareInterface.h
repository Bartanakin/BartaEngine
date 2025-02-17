#pragma once
#include <Hitbox/HitboxAwareConcept.h>
#include <Hitbox/HitboxInterface.h>
#include <pch.h>

namespace Barta {

class HitboxAware {
public:
    HitboxAware() = default;
    virtual ~HitboxAware() = default;

    virtual std::unique_ptr<const HitboxInterface> getHitbox() const = 0;
};

static_assert(HitboxAwareConcept<HitboxAware>);
}
