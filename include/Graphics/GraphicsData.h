#pragma once
#include "Graphics/BartaSprite.h"
#include <Geometrics/Transformation.h>

namespace Barta {

class GraphicsData {
public:
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
