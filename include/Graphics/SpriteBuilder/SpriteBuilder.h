#pragma once
#include "../../Geometrics/Vector2f.h"
#include "../Color.h"

namespace Barta {
class SpriteBuilder {
public:
    SpriteBuilder() noexcept = default;
    ~SpriteBuilder() noexcept = default;

    SpriteBuilder* setColor1(
        Color color
    ) {
        this->color1 = color;
        return this;
    }

    SpriteBuilder* setColor2(
        Color color
    ) {
        this->color2 = color;
        return this;
    }

    SpriteBuilder* setColor3(
        Color color
    ) {
        this->color3 = color;
        return this;
    }

    SpriteBuilder* setColor4(
        Color color
    ) {
        this->color4 = color;
        return this;
    }

    SpriteBuilder* setAllColors(
        Color color
    ) {
        this->color1 = color;
        this->color2 = color;
        this->color3 = color;
        this->color4 = color;

        return this;
    }

    SpriteBuilder* setVertex1(
        Point vertex
    ) {
        this->vertex1 = vertex;
        return this;
    }

    SpriteBuilder* setVertex2(
        Point vertex
    ) {
        this->vertex2 = vertex;
        return this;
    }

    SpriteBuilder* setVertex3(
        Point vertex
    ) {
        this->vertex3 = vertex;
        return this;
    }

    SpriteBuilder* setSize(
        Vector size
    ) {
        this->size = size;
        return this;
    }

    SpriteBuilder* setString(
        std::string string
    ) {
        this->string = string;
        return this;
    }

    SpriteBuilder* setFontSize(
        int fontSize
    ) {
        this->fontSize = fontSize;
        return this;
    }

protected:
    Color color1;
    Color color2;
    Color color3;
    Color color4;

    Point vertex1;
    Point vertex2;
    Point vertex3;

    Vector size;
    std::string string;
    int fontSize;
};
}
