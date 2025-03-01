#pragma once
#include <Dynamics/DynamicsDTO.h>
#include <Graphics/GraphicsData.h>
#include <Hitbox/HitboxInterface.h>
#include <ObjectManagerInterface.h>
#include <pch.h>

namespace Barta::SceneLoader {

template<typename ObjectJsonDecoderManager, typename ListManager>
concept ObjectJsonDecoderManagerConcept = requires(
    ObjectJsonDecoderManager manager,
    const json& json,
    const GraphicsData& graphicsData,
    std::unique_ptr<HitboxInterface> hitbox,
    const DynamicsDTO& dynamicsDto,
    ListManager& listManager,
    ObjectManagerInterface& objectManager
) {
    { manager.template decodeObjects<ListManager>(json, graphicsData, std::move(hitbox), dynamicsDto, listManager, objectManager) };
};

}
