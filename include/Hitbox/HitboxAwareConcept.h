//
// Created by bartanakin on 11/10/24.
//

#pragma once
#include "HitboxInterface.h"
#include "pch.h"

namespace Barta {
template<typename T>
concept HitboxAwareConcept = requires(const T t) {
    { t.getHitbox() } -> std::same_as<std::unique_ptr<const HitboxInterface>>;
};

}
