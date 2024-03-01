#pragma once
#include "../../pch.h"
#include "../BartaSprite.h"
#include "CircleSprite.h"
#include "RectangleWithColorsSprite.h"
#include "SpriteBuilder.h"
#include "StringSprite.h"

namespace Barta{
    class SpriteMerger {
        public:
        SpriteMerger() noexcept;

        SpriteMerger* addRectanglewithColors(const RectangleWithColorsSprite& addRectanglewithColors);
        SpriteMerger* addCircleSprite(const CircleSprite& circleSprite);
        SpriteMerger* addString(const Barta::StringSprite& stringSprite);
        
        BartaSprite merge(bool reloadCache);

        protected:

        std::vector<float> data;
        std::vector<SpriteType> types;
    };
}

