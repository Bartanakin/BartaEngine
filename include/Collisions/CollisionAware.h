#pragma once

#include "../Dynamics/DynamicsAwareInterface.h"
#include "../Hitbox/HitboxAwareInterface.h"
#include "../ReduceableList.h"
#include "pch.h"

namespace Barta {

template<typename T>
concept CollisionAware = requires(T t) {
    { t.getHitbox() } -> std::same_as<std::unique_ptr<const HitboxInterface>>;
    { t.getDynamicsDTO() } -> std::same_as<DynamicsDTO&>;
};

struct CollisionAwareStub {
    std::unique_ptr<const HitboxInterface> getHitbox();
    DynamicsDTO& getDynamicsDTO();
};
}
