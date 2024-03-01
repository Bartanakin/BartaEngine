#pragma once

#include "pch.h"
#include "../Dynamics/DynamicsAwareInterface.h"
#include "../Hitbox/HitboxAwareInterface.h"
#include "../ReduceableList.h"

namespace Barta {
    template<typename T>
    concept StaticCollisionAware = requires (T t) {
        { t.getHitbox() } -> std::same_as<std::unique_ptr<const HitboxInterface>>;
        { t.getDynamicsDTO() } -> std::same_as<const DynamicsDTO&>;
    };

    struct StaticCollisionAwareStub {
        std::unique_ptr<const HitboxInterface> getHitbox();
        const DynamicsDTO& getDynamicsDTO();
    };
}