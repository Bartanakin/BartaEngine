#pragma once
#include "../Color.h"
#include "../../Geometrics/Vector2f.h"

namespace Barta {
struct ArrowSprite {
public:
    ArrowSprite(
        Vector2f ogrin,
        Vector2f value,
        float thickness,
        float capSize,
        Color color
    ) noexcept:
        ogrin(ogrin),
        value(value),
        thickness(thickness),
        capSize(capSize),
        color(color) {}

    const Vector2f ogrin;
    const Vector2f value;
    const float thickness;
    const float capSize;
    const Color color;
};
}
