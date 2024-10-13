#pragma once
#include "../../pch.h"
#include "../BartaSprite.h"
#include "CircleSprite.h"
#include "RectangleWithColorsSprite.h"
#include "SpriteBuilder.h"
#include "StringSprite.h"
#include "TriangleSprite.h"

namespace Barta {
class SpriteMerger {
public:
    SpriteMerger() noexcept;

    SpriteMerger* addRectangleWithColors(const RectangleWithColorsSprite& addRectangleWithColors);

    SpriteMerger* addCircleSprite(const CircleSprite& circleSprite);

    SpriteMerger* addString(const StringSprite& stringSprite);

    SpriteMerger* addTriangle(const TriangleSprite& triangleSprite);

    BartaSprite merge(bool reloadCache);

protected:
    std::vector<float> data;
    std::vector<SpriteType> types;
};
}
