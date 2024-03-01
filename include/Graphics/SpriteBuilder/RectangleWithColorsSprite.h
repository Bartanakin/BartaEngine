#pragma once
#include "../Color.h"
#include "../../Geometrics/BartaShapes/AABB.h"

namespace Barta{
    struct RectangleWithColorsSprite {
        public:
        RectangleWithColorsSprite(
            Vector2f origin,
            Vector2f size,
            Color leftTopColor,
            Color rightTopColor,
            Color rightBottomColor,
            Color leftBottomColor
        ) noexcept :
            aabb({origin, size}),
            leftTopColor(leftTopColor),
            rightTopColor(rightTopColor),
            rightBottomColor(rightBottomColor),
            leftBottomColor(leftBottomColor)
        {}

        AABB aabb;
        Color leftTopColor;
        Color rightTopColor;
        Color rightBottomColor;
        Color leftBottomColor;
    };
}

