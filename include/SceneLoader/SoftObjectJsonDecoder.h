#pragma once
#include "Objects/Soft/MeshLoader/MshDataParser.h"
#include "Objects/Soft/MeshLoader/SurfaceFacesMshParserDecorator.h"
#include <Objects/Soft/MeshLoader/MshDataLoader.h>
#include <Objects/Soft/SoftObject.h>
#include <SceneLoader/ObjectJsonDecoder.h>
#include <SceneLoader/ObjectJsonDecoderConcept.h>
#include <pch.h>

template<>
class Barta::SceneLoader::ObjectJsonDecoder<Barta::Objects::Soft::SoftObject> {
    using SoftObject = Barta::Objects::Soft::SoftObject;

public:
    SoftObject* decodeObject(
        const json& json,
        const GraphicsData& graphicsData,
        std::unique_ptr<HitboxInterface> hitbox,
        const DynamicsDTO& dynamicsDto
    ) {
        const auto& jsonType = json.at("type");
        if (!jsonType.is_string()) {
            return nullptr;
        }

        if (jsonType.get<std::string>() != "BARTA_SOFT_OBJECT") {
            return nullptr;
        }

        const auto& meshType = json.at("meshType");
        if (!meshType.is_string()) {
            return nullptr;
        }

        if (meshType.get<std::string>() == "msh") {
            auto mshDecoder = Objects::Soft::MeshLoader::MshDataLoader();
            auto meshParser = Objects::Soft::MeshLoader::MshDataParser();
            auto meshParserDecorator = Objects::Soft::MeshLoader::SurfaceFacesMshParserDecorator(meshParser);
            std::string fileName = json.at("sourceFileName");

            return new SoftObject(
                meshParserDecorator.parse(mshDecoder.loadMshDataFromFile(std::filesystem::path("meshes") / std::filesystem::path(fileName))),
                dynamicsDto
            );
        }

        return nullptr;
    }

    static_assert(ObjectJsonDecoderConcept<ObjectJsonDecoder, SoftObject>);
};
