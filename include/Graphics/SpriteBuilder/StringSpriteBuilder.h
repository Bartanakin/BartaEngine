#pragma once

#include "SpriteBuilder.h"
#include "StringSprite.h"
namespace Barta {
class StringSpriteBuilder : public SpriteBuilder {
public:
    StringSprite build() noexcept;
};

};
