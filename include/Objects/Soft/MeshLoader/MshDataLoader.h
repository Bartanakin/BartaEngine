#pragma once
#include <Objects/Soft/MeshLoader/MshDataLoaderInterface.h>
#include <pch.h>

namespace Barta::Objects::Soft::MeshLoader {
class MshDataLoader: public MshDataLoaderInterface {
    static constexpr std::array<std::string, 1> ALLOWED_VERSIONS = {"4.1"};

public:
    MshData loadMshDataFromFile(const std::filesystem::path& filePath) const override;
};
}
