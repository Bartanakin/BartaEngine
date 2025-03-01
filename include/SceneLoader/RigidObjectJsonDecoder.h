#pragma once
#include <Objects/Rigid/RigidObject.h>
#include <SceneLoader/ObjectJsonDecoder.h>
#include <pch.h>

namespace Barta::SceneLoader {

template<>
class ObjectJsonDecoder<RigidObjectInterface> {
public:
    RigidObjectInterface* decodeObject(
        const json& json,
        const GraphicsData& graphicsData,
        std::unique_ptr<HitboxInterface> hitbox,
        const DynamicsDTO& dynamicsDto
    ) {
        const auto& jsonType = json.at("type");
        if (!jsonType.is_string()) {
            return nullptr;
        }

        if (jsonType.get<std::string>() != "BARTA_RIGID_OBJECT") {
            return nullptr;
        }

        return new RigidObject(graphicsData, std::move(hitbox), dynamicsDto);
    }
};

static_assert(ObjectJsonDecoderConcept<ObjectJsonDecoder<RigidObjectInterface>, RigidObjectInterface>);
}
