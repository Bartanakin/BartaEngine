#pragma once
#include <Geometrics/BartaShapes/Circle.h>
#include <Graphics/Color.h>
#include <utility>

namespace Barta {
struct CircleSprite {
    CircleSprite(
        Circle circle,
        Color color,
        float meshDensity
    ) noexcept:
        circle(std::move(circle)),
        color(color),
        meshDensity(meshDensity) {}

    Circle circle;
    Color color;
    float meshDensity;
};
}
