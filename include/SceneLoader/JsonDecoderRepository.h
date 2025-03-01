#pragma once
#include <Graphics/GraphicsData.h>
#include <Hitbox/HitboxInterface.h>

namespace Barta::SceneLoader {

class JsonDecoderRepository {
public:
    std::unique_ptr<HitboxInterface> decodeHitbox(const json& json) const;

    GraphicsData decodeGraphicsData(const json& json) const;
};

}
