#pragma once
#include <Graphics/Color.h>
#include <Graphics/SpriteBuilder/CircleSprite.h>
#include <Graphics/SpriteBuilder/RectangleWithColorsSprite.h>
#include <Graphics/SpriteBuilder/StringSprite.h>
#include <Graphics/SpriteBuilder/TriangleSprite.h>
#include <pch.h>

namespace Barta {
class SpriteBuilder {
public:
    SpriteBuilder() noexcept = default;
    ~SpriteBuilder() noexcept = default;

    PrecisionType radius;

    Color color;
    Color color1;
    Color color2;
    Color color3;
    Color color4;

    Point vertex;
    Point origin;
    Point center;
    Point vertex1;
    Point vertex2;
    Point vertex3;

    Vector size;
    std::string string;
    int fontSize;

    float meshDensity;

    CircleSprite buildCircleSprite() const {
        return {
            {this->radius, this->center},
            this->color,
            this->meshDensity
        };
    }

    RectangleWithColorsSprite buildRectangleWithColorsSprite() const {
        return {this->origin, this->size, this->color1, this->color2, this->color3, this->color4};
    }

    RectangleWithColorsSprite buildRectangleSprite() const { return {this->origin, this->size, this->color, this->color, this->color, this->color}; }

    StringSprite buildStringSprite() const noexcept { return {this->origin, this->string, this->fontSize}; }

    TriangleSprite buildTriangleWithColorsSprite() const noexcept {
        return {
            {this->vertex1, this->vertex2, this->vertex3},
            this->color1,
            this->color2,
            this->color3
        };
    }

    TriangleSprite buildTriangleSprite() const noexcept {
        return {
            {this->vertex1, this->vertex2, this->vertex3},
            this->color,
            this->color,
            this->color
        };
    }
};

inline void from_json(
    const json& j,
    SpriteBuilder& sprite
) {
    if (j.contains("radius")) {
        j.at("radius").get_to(sprite.radius);
    }

    if (j.contains("color")) {
        j.at("color").get_to(sprite.color);
    }

    if (j.contains("color1")) {
        j.at("color1").get_to(sprite.color1);
    }

    if (j.contains("color2")) {
        j.at("color2").get_to(sprite.color2);
    }

    if (j.contains("color3")) {
        j.at("color3").get_to(sprite.color3);
    }

    if (j.contains("color4")) {
        j.at("color4").get_to(sprite.color4);
    }

    if (j.contains("vertex")) {
        j.at("vertex").get_to(sprite.vertex);
    }

    if (j.contains("origin")) {
        j.at("origin").get_to(sprite.origin);
    }

    if (j.contains("center")) {
        j.at("center").get_to(sprite.center);
    }

    if (j.contains("vertex1")) {
        j.at("vertex1").get_to(sprite.vertex1);
    }

    if (j.contains("vertex2")) {
        j.at("vertex2").get_to(sprite.vertex2);
    }

    if (j.contains("vertex3")) {
        j.at("vertex3").get_to(sprite.vertex3);
    }

    if (j.contains("size")) {
        j.at("size").get_to(sprite.size);
    }

    if (j.contains("string")) {
        j.at("string").get_to(sprite.string);
    }

    if (j.contains("fontSize")) {
        j.at("fontSize").get_to(sprite.fontSize);
    }

    if (j.contains("meshDensity")) {
        j.at("meshDensity").get_to(sprite.meshDensity);
    }
}
}
