#pragma once
#include <ObjectManagerInterface.h>
#include <SceneLoader/JsonDecoderRepository.h>
#include <pch.h>

namespace Barta::SceneLoader {

template<typename ObjectJsonDecoderManager, typename ListManager, typename EventsLogger>
    requires ObjectJsonDecoderManagerConcept<ObjectJsonDecoderManager, ListManager>
             && requires(EventsLogger EL, Events::Events::CameraTransformationEvent event) {
                    { EL.logEvent(std::move(event)) };
                } class RootJsonDecoder {
public:
    RootJsonDecoder(
        ListManager& listManager,
        ObjectManagerInterface& objectManager,
        EventsLogger& eventsLogger
    ) noexcept:
        listManager(listManager),
        objectManager(objectManager),
        eventsLogger(eventsLogger) {}

    void decode(
        const json& json
    ) {
        JsonDecoderRepository repository;
        const auto& camera = json.at("camera");
        if (camera.is_object()) {
            this->eventsLogger.logEvent(std::move(repository.decodeCamera(camera)));
        }

        const auto& objects = json.at("objects");
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
    EventsLogger& eventsLogger;
};

}
