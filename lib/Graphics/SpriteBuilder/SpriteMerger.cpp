#include <Graphics/SpriteBuilder/SpriteMerger.h>

Barta::SpriteMerger::SpriteMerger() noexcept:
    data({}),
    types({}) {}

Barta::SpriteMerger* Barta::SpriteMerger::addRectangleWithColors(
    const RectangleWithColorsSprite& addRectangleWithColors
) {
    this->types.push_back(SpriteType::RECTANGLE_WITH_COLORS);

    for (const auto& vector: {
             addRectangleWithColors.aabb.getLeftTop().toVector(),
             addRectangleWithColors.aabb.getWidthHeight(),
         }) {
        this->data.push_back(vector.x());
        this->data.push_back(vector.y());
        this->data.push_back(vector.z());
    }

    for (const auto& color:
         {addRectangleWithColors.leftTopColor,
          addRectangleWithColors.rightTopColor,
          addRectangleWithColors.rightBottomColor,
          addRectangleWithColors.leftBottomColor}) {
        this->data.push_back(color.r);
        this->data.push_back(color.g);
        this->data.push_back(color.b);
        this->data.push_back(color.a);
    }

    return this;
}

Barta::SpriteMerger* Barta::SpriteMerger::addCircleSprite(
    const CircleSprite& circleSprite
) {
    this->types.push_back(SpriteType::CIRCLE);

    this->data.push_back(circleSprite.circle.getCenter().x());
    this->data.push_back(circleSprite.circle.getCenter().y());
    this->data.push_back(circleSprite.circle.getCenter().z());
    this->data.push_back(circleSprite.circle.getRadius());

    this->data.push_back(circleSprite.color.r);
    this->data.push_back(circleSprite.color.g);
    this->data.push_back(circleSprite.color.b);
    this->data.push_back(circleSprite.color.a);

    return this;
}

Barta::SpriteMerger* Barta::SpriteMerger::addString(
    const Barta::StringSprite& stringSprite
) {
    this->types.push_back(SpriteType::VARCHAR256);
    this->data.push_back(stringSprite.origin.x());
    this->data.push_back(stringSprite.origin.y());
    this->data.push_back(stringSprite.origin.z());
    this->data.push_back(static_cast<float>(stringSprite.fontSize));
    size_t size = stringSprite.string.size();
    if (size > 256) {
        size = 256;
    }

    this->data.insert(this->data.end(), 64, 0.f);
    std::copy(stringSprite.string.begin(), stringSprite.string.end(), this->data.end() - 64);

    return this;
}

Barta::SpriteMerger* Barta::SpriteMerger::addTriangle(
    const TriangleSprite& triangleSprite
) {
    this->types.push_back(SpriteType::TRIANGLE);

    for (const auto& vector: {triangleSprite.triangle.p1, triangleSprite.triangle.p2, triangleSprite.triangle.p3}) {
        this->data.push_back(vector.x());
        this->data.push_back(vector.y());
        this->data.push_back(vector.z());
    }

    for (const auto& color: {triangleSprite.color1, triangleSprite.color2, triangleSprite.color3}) {
        this->data.push_back(color.r);
        this->data.push_back(color.g);
        this->data.push_back(color.b);
        this->data.push_back(color.a);
    }

    return this;
}

Barta::BartaSprite Barta::SpriteMerger::merge(
    bool reloadCache
) {
    auto sprite = BartaSprite(reloadCache, std::move(this->data), std::move(this->types));

    this->data = {};
    this->types = {};

    return sprite;
}
