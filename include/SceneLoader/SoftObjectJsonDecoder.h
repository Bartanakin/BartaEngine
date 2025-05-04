#pragma once
#include "Objects/Soft/MshLoader/DirichletConditionPlugin.h"
#include "Objects/Soft/MshLoader/ElementsPlugin.h"
#include "Objects/Soft/MshLoader/EntitiesPlugin.h"
#include "Objects/Soft/MshLoader/MeshFormatPlugin.h"
#include "Objects/Soft/MshLoader/NodesPlugin.h"
#include "Objects/Soft/MshParser/DirichletConditionParserDecorator.h"
#include "Objects/Soft/MshParser/MshDataParser.h"
#include "Objects/Soft/MshParser/SurfaceFacesMshParserDecorator.h"
#include "Objects/Soft/MshParser/TetrahedralElementLoaderDecorator.h"
#include <Objects/Soft/MshLoader/MshDataLoader.h>
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
            auto mshDecoder = Objects::Soft::MshLoader::MshDataLoader();

            mshDecoder.registerPlugin(std::make_unique<Objects::Soft::MshLoader::MeshFormatPlugin>());
            mshDecoder.registerPlugin(std::make_unique<Objects::Soft::MshLoader::DirichletConditionPlugin>());
            mshDecoder.registerPlugin(std::make_unique<Objects::Soft::MshLoader::EntitiesPlugin>());
            mshDecoder.registerPlugin(std::make_unique<Objects::Soft::MshLoader::NodesPlugin>());
            mshDecoder.registerPlugin(std::make_unique<Objects::Soft::MshLoader::ElementsPlugin>());

            auto meshParser = Objects::Soft::MshParser::MshDataParser();
            auto meshParserDecorator1 = Objects::Soft::MshParser::DirichletConditionParserDecorator(meshParser);
            auto meshParserDecorator2 = Objects::Soft::MshParser::TetrahedralElementLoaderDecorator(meshParserDecorator1);
            auto meshParserDecorator3 = Objects::Soft::MshParser::SurfaceFacesMshParserDecorator(meshParserDecorator2);
            std::string fileName = json.at("sourceFileName");

            return new SoftObject(
                meshParserDecorator3.parse(mshDecoder.loadMshDataFromFile(std::filesystem::path("meshes") / std::filesystem::path(fileName))),
                dynamicsDto
            );
        }

        return nullptr;
    }

    static_assert(ObjectJsonDecoderConcept<ObjectJsonDecoder, SoftObject>);
};
