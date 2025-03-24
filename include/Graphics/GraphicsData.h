#pragma once
#include <Geometrics/Transformation.h>
#include <Graphics/BartaSprite.h>

namespace Barta {

struct GraphicsData {
    Transformation transformation;
    BartaSprite resource;
    int z_index;

    GraphicsData() = default;

    GraphicsData(
        Transformation transformation,
        BartaSprite resource,
        int z_index
    ):
        transformation(std::move(transformation)),
        resource(resource),
        z_index(z_index) {}
};
}
