#pragma once

#include <Dynamics/DynamicsDTOCollection.h>
#include <Hitbox/HitboxAwareInterface.h>
#include <pch.h>

namespace Barta {

template<typename T>
concept CollisionAware = requires(T t) {
    { t.getHitbox() } -> std::same_as<std::unique_ptr<const HitboxInterface>>;
    { t.getDynamicsDTOs() } -> std::same_as<DynamicsDTOCollection&>;
};

struct CollisionAwareStub {
    std::unique_ptr<const HitboxInterface> getHitbox();
    DynamicsDTOCollection& getDynamicsDTOs();
};
}
