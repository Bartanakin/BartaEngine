#pragma once
#include "RectangleWithColorsSprite.h"
#include "SpriteBuilder.h"

namespace Barta{
    class RectangleWithColorsSpriteBuilder : public SpriteBuilder {
        public:

        RectangleWithColorsSprite build() const;
    };
}

