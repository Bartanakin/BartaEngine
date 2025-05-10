#pragma once
#include <pch.h>

namespace Barta {
enum class SpriteType {
    // x, y, z, x_size, y_size, z_size,
    // left-top-color (rgba),
    // right-top-color (rgba),
    // right-bottom-color (rgba),
    // left-bottom-color (rgba)
    RECTANGLE_WITH_COLORS,
    /*
        x, y, z, // center coordinates
        radius,
        color (rgba),
        meshDensity
    */
    CIRCLE,
    /*
        x, y, z, // center coordinates
        radius,
        color (rgba),
        meshDensity
    */
    BALL,
    /*
        x, y, z, // top-left coordinates
        font_size,
        char[256]
    */
    /// Unsupported with OpenGL
    VARCHAR256,
    /*
     * x1, y1, z1
     * x2, y2, z2,
     * x3, y3, z3,
     * color1 (rgba),
     * color2 (rgba),
     * color3 (rgba)
     */
    TRIANGLE
};

class BartaSprite {
public:
    BartaSprite(
        int resource
    ) noexcept:
        resource(resource),
        doReloadCache(false),
        data({}),
        spriteTypes({}) {}

    BartaSprite(
        bool doReloadCache,
        std::vector<float> data,
        std::vector<SpriteType> spriteTypes
    ) noexcept:
        resource(0),
        doReloadCache(doReloadCache),
        data(std::move(data)),
        spriteTypes(std::move(spriteTypes)) {}

    BartaSprite() = default;
    ~BartaSprite() = default;

    int getResourceId() const { return this->resource; }

    bool reloadCache() const { return this->doReloadCache; }

    const std::vector<float>& getData() const { return this->data; }

    const std::vector<SpriteType>& getSpriteType() const { return this->spriteTypes; }

    static unsigned int getSpriteTypeSize(
        SpriteType type
    ) {
        switch (type) {
        case SpriteType::RECTANGLE_WITH_COLORS: return 6 + 4 * 4;
        case SpriteType::CIRCLE: return 9;
        case SpriteType::BALL: return 9;
        case SpriteType::VARCHAR256: return 256 / 4 + 4;
        case SpriteType::TRIANGLE: return 9 + 3 * 4;
        }

        return 0;
    }

protected:
    int resource;
    bool doReloadCache;
    std::vector<float> data;
    std::vector<SpriteType> spriteTypes;
};
}
