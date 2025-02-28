//
// Created by bartanakin on 11/2/24.
//

#include <Graphics/GraphicsDataTransformer.h>
#include <Geometrics/BartaShapes/OBB.h>
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
         obb.getTransformation().getMatrix() * Point(obb.getWidthHeight().x(), 0.f, 0.f),
         obb.getTransformation().getMatrix() * (obb.getWidthHeight() + Point::Zero())},
        this->color1,
        this->color1,
        this->color1
    ));
    merger.addTriangle(Barta::TriangleSprite(
        {obb.getFirstVertex(),
         obb.getTransformation().getMatrix() * (obb.getWidthHeight() + Point::Zero()),
         obb.getTransformation().getMatrix() * Point(0.f, obb.getWidthHeight().y(), 0.f)},
        this->color1,
        this->color1,
        this->color1
    ));

    return {Transformation::Identity(), merger.merge(false), 4};
}
