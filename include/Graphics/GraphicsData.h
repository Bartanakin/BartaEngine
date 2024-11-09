#pragma once
#include "Geometrics/TransformableInterface.h"
#include "Graphics/BartaSprite.h"

namespace Barta {

class GraphicsData {
public:
    std::unique_ptr<TransformableInterface> transformable;
    BartaSprite resource;
    int z_index;

    GraphicsData() = default;

    GraphicsData(
        std::unique_ptr<TransformableInterface> transformable,
        BartaSprite resource,
        int z_index
    ):
        transformable(std::move(transformable)),
        resource(resource),
        z_index(z_index) {}
};
}
