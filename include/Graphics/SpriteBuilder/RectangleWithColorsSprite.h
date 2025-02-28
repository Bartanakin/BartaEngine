#pragma once
#include <Geometrics/BartaShapes/AABB.h>
#include <Graphics/Color.h>

namespace Barta {
struct RectangleWithColorsSprite {
    RectangleWithColorsSprite() noexcept = default;

    RectangleWithColorsSprite(
        Point origin,
        Vector size,
        Color leftTopColor,
        Color rightTopColor,
        Color rightBottomColor,
        Color leftBottomColor
    ) noexcept:
        aabb({origin, size}),
        leftTopColor(leftTopColor),
        rightTopColor(rightTopColor),
        rightBottomColor(rightBottomColor),
        leftBottomColor(leftBottomColor) {}

    AABB aabb;
    Color leftTopColor;
    Color rightTopColor;
    Color rightBottomColor;
    Color leftBottomColor;
};
}
