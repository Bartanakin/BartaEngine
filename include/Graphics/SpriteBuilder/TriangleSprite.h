#pragma once
#include "../Color.h"
#include <Geometrics/BartaShapes/Triangle.h>

namespace Barta {
struct TriangleSprite {
public:
    TriangleSprite(
        Triangle triangle,
        Color color1,
        Color color2,
        Color color3
    ) noexcept:
        triangle(triangle),
        color1(color1),
        color2(color2),
        color3(color3) {}

    Triangle triangle;
    Color color1;
    Color color2;
    Color color3;
};
}
