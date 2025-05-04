#pragma once
#include "MshDataLoaderInterface.h"
#include "MshLoaderPluginInterface.h"
#include <pch.h>

namespace Barta::Objects::Soft::MshLoader {
class MshDataLoader: public MshDataLoaderInterface {
    static constexpr std::array<std::string, 1> ALLOWED_VERSIONS = {"4.1"};

public:
    MshData loadMshDataFromFile(const std::filesystem::path& filePath) const override;

    void registerPlugin(std::unique_ptr<MshLoaderPluginInterface> plugin);

private:
    std::vector<std::unique_ptr<MshLoaderPluginInterface>> plugins;
};
}
