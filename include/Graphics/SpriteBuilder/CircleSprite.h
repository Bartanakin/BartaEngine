#pragma once
#include "../Color.h"
#include "../../Geometrics/BartaShapes/Circle.h"

namespace Barta{
    struct CircleSprite {
        public:
        CircleSprite(
            Circle circle,
            Color color
        ) noexcept :
            circle(circle),
            color(color)
        {}

        Circle circle;
        Color color;
    };
}

