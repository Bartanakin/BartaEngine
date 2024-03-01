#pragma once

#include "Geometrics/Vector2f.h"
namespace Barta {

class StringSprite {
public:
    StringSprite(
        Barta::Vector2f origin,
        std::string string,
        int fontSize
    ) noexcept
        : origin(origin),
          string(string),
          fontSize(fontSize)
    {}

    Barta::Vector2f origin;
    std::string string;
    int fontSize;
};

} // namespace Barta
