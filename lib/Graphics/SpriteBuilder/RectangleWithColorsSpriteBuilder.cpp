#include <Graphics/SpriteBuilder/RectangleWithColorsSpriteBuilder.h>

Barta::RectangleWithColorsSprite Barta::RectangleWithColorsSpriteBuilder::build() const {
    return RectangleWithColorsSprite(
        this->vertex1,
        this->size,
        this->color1,
        this->color2,
        this->color3,
        this->color4
    );
}