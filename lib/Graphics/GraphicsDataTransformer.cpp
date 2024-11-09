//
// Created by bartanakin on 11/2/24.
//

#include <Graphics/GraphicsDataTransformer.h>
#include <Graphics/SFML_GraphicsBridge.h>
#include <Graphics/SpriteBuilder/SpriteMerger.h>

Barta::GraphicsDataTransformer::GraphicsDataTransformer(
    Color color1
) noexcept:
    color1(color1) {}

Barta::GraphicsData Barta::GraphicsDataTransformer::fromOBB(
    const OBB& obb
) const {
    auto merger = Barta::SpriteMerger();

    merger.addTriangle(Barta::TriangleSprite(
        {obb.getFirstVertex(),
         Vector2f(obb.getWidthHeight().x, 0.f).rotated(obb.getRotation()) + obb.getFirstVertex(),
         obb.getWidthHeight().rotated(obb.getRotation()) + obb.getFirstVertex()},
        this->color1,
        this->color1,
        this->color1
    ));
    merger.addTriangle(Barta::TriangleSprite(
        {obb.getFirstVertex(),
         obb.getWidthHeight().rotated(obb.getRotation()) + obb.getFirstVertex(),
         Vector2f(0.f, obb.getWidthHeight().y).rotated(obb.getRotation()) + obb.getFirstVertex()},
        this->color1,
        this->color1,
        this->color1
    ));

    return {Barta::SFML_GraphicsBridge::createNewTransformableInstance(), merger.merge(false), 4};
}
