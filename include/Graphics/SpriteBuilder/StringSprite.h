#pragma once
#include <Geometrics/Point.h>
#include <pch.h>

namespace Barta {

class StringSprite {
public:
    StringSprite(
        Point origin,
        std::string string,
        int fontSize
    ) noexcept:
        origin(std::move(origin)),
        string(std::move(string)),
        fontSize(fontSize) {}

    Point origin;
    std::string string;
    int fontSize;
};

} // namespace Barta
