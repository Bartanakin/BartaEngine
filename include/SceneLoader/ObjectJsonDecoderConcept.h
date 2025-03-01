#pragma once
#include <Dynamics/DynamicsDTO.h>
#include <Graphics/GraphicsData.h>
#include <Hitbox/HitboxInterface.h>
#include <pch.h>

namespace Barta::SceneLoader {
template<typename ObjectJsonDecoder, typename T>
concept ObjectJsonDecoderConcept = requires(
    ObjectJsonDecoder objectJsonDecoder,
    const json& json,
    const GraphicsData& graphicsData,
    std::unique_ptr<HitboxInterface> hitbox,
    const DynamicsDTO& dynamicsDto
) {
    { objectJsonDecoder.decodeObject(json, graphicsData, std::move(hitbox), dynamicsDto) } -> std::same_as<T*>;
};
}
