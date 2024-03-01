#pragma once
#include "../pch.h"

namespace Barta{
    enum class SpriteType {
        // x, y, z, x_size, y_size, z_size,
        // left-top-color (rgba),
        // right-top-color (rgba),
        // right-bottom-color (rgba),
        // left-bottom-color (rgba)
        RECTABGLE_WITH_COLORS,
        /*
            x, y, z, // ceter coordinates
            radius,
            color (rgba)
        */
        CIRCLE,
        /*
            x, y, z, // top-left coordinates
            font_size,
            char[256]
        */
        VARCHAR256
    };

    class BartaSprite {
    public:
		BartaSprite(
            int resource
        ) noexcept :
            resource(resource),
            doReloadCache(false),
            data({}),
            spriteTypes({})
        {}
		BartaSprite(
            bool doReloadCache,
            std::vector<float> data,
            std::vector<SpriteType> spriteTypes
        ) noexcept :
            resource(0),
            doReloadCache(doReloadCache),
            data(std::move(data)),
            spriteTypes(std::move(spriteTypes))
        {}
		~BartaSprite() = default;

        inline int getResourceId() const { return this->resource; }

        inline bool reloadCache() const { return this->doReloadCache; }

        inline const std::vector<float>& getData() const { return this->data; } 

        inline const std::vector<SpriteType>& getSpriteType() const { return this->spriteTypes; }

        protected:

        int resource;
        bool doReloadCache;
        std::vector<float> data;
        std::vector<SpriteType> spriteTypes;
    };
}

