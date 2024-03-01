#pragma once
#include "Geometrics/Vector2f.h"
#include "pch.h"

namespace Barta {

template<typename T>
concept PositionAware = requires (T t) {
    { t.getPosition() } -> std::same_as<Vector2f>;
};

} // namespace Barta
