#pragma once
#include <Dynamics/DynamicsDTO.h>
#include <Graphics/GraphicsData.h>
#include <Hitbox/HitboxInterface.h>
#include <pch.h>

namespace Barta::SceneLoader {

// This is just an example template. It should always have a specialization to be instantiated.
// Remember to include the header file with specialization in your main header file.
template<typename T>
class ObjectJsonDecoder {
public:
    T* decodeObject(
        const json& json,
        const GraphicsData& graphicsData,
        std::unique_ptr<HitboxInterface> hitbox,
        const DynamicsDTO& dynamicsDto
    ) {
        static_assert(false, "This is a pure static interface. Use a class specialization.");
    }
};

}
