#pragma once
#include <ObjectManagerInterface.h>
#include <SceneLoader/JsonDecoderRepository.h>
#include <pch.h>

namespace Barta::SceneLoader {

template<typename ObjectJsonDecoderManager, typename ListManager>
    requires ObjectJsonDecoderManagerConcept<ObjectJsonDecoderManager, ListManager> class RootJsonDecoder {
public:
    RootJsonDecoder(
        ListManager& listManager,
        ObjectManagerInterface& objectManager
    ) noexcept:
        listManager(listManager),
        objectManager(objectManager) {}

    void decode(
        const json& json
    ) {
        const auto& objects = json.at("objects");
        JsonDecoderRepository repository;
        if (objects.is_array()) {
            for (const auto& objectJson: objects) {
                DynamicsDTO dynamicsData;
                if (objectJson.contains("dynamicsData")) {
                    dynamicsData = objectJson.at("dynamicsData").get<DynamicsDTO>();
                } else {
                    dynamicsData = {};
                }

                ObjectJsonDecoderManager().template decodeObjects<ListManager>(
                    objectJson,
                    repository.decodeGraphicsData(objectJson),
                    std::move(repository.decodeHitbox(objectJson)),
                    dynamicsData,
                    this->listManager,
                    this->objectManager
                );
            }
        }
    }

private:
    ListManager& listManager;
    ObjectManagerInterface& objectManager;
};

}
