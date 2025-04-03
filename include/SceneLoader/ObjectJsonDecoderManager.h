#pragma once
#include <ListManagerConcept.h>
#include <ObjectManagerInterface.h>
#include <SceneLoader/ObjectJsonDecoderConcept.h>
#include <SceneLoader/ObjectJsonDecoderManagerConcept.h>
// Important include to define the specialization for ObjectJsonDecoder
#include <SceneLoader/RigidObjectJsonDecoder.h>
#include <SceneLoader/SoftObjectJsonDecoder.h>

namespace Barta::SceneLoader {

template<typename T, typename... Ts>
class ObjectJsonDecoderManager: public ObjectJsonDecoderManager<T>, public ObjectJsonDecoderManager<Ts...> {
public:
    ObjectJsonDecoderManager():
        ObjectJsonDecoderManager<T>(),
        ObjectJsonDecoderManager<Ts...>() {}

    template<typename ListManager>
    void decodeObjects(
        const json& json,
        const GraphicsData& graphicsData,
        std::unique_ptr<HitboxInterface> hitbox,
        const DynamicsDTO& dynamicsDto,
        ListManager& listManager,
        ObjectManagerInterface& objectManager
    ) {
        ObjectJsonDecoderManager<T>::template decodeObjects<ListManager>(
            json,
            graphicsData,
            std::move(hitbox),
            dynamicsDto,
            listManager,
            objectManager
        );
        ObjectJsonDecoderManager<Ts...>::template decodeObjects<ListManager>(
            json,
            graphicsData,
            std::move(hitbox),
            dynamicsDto,
            listManager,
            objectManager
        );
    }
};

template<typename T>
class ObjectJsonDecoderManager<T> {
public:
    template<typename ListManager>
        requires ListManagerConcept<ListManager, T> && ObjectJsonDecoderConcept<ObjectJsonDecoder<T>, T> void decodeObjects(
        const json& json,
        const GraphicsData& graphicsData,
        std::unique_ptr<HitboxInterface> hitbox,
        const DynamicsDTO& dynamicsDto,
        ListManager& listManager,
        ObjectManagerInterface& objectManager
    ) {
        T* object = ObjectJsonDecoder<T>().decodeObject(json, graphicsData, std::move(hitbox), dynamicsDto);
        if (object == nullptr) {
            return;
        }

        listManager.addObject(object);
        objectManager.addGraphicsObject(object);
        objectManager.addDynamicsObject(object);
        objectManager.addNewObject(object);
    }
};

static_assert(ObjectJsonDecoderManagerConcept<ObjectJsonDecoderManager<BartaObjectInterface>, StaticObjectManager<BartaObjectInterface>>);
}
