#include <Objects/Soft/MshLoader/MshDataLoader.h>

namespace Barta::Objects::Soft::MshLoader {
MshData MshDataLoader::loadMshDataFromFile(
    const std::filesystem::path& filePath
) const {
    std::ifstream infile(filePath.string());
    if (!infile) {
        throw std::runtime_error("Failed to open file: " + filePath.string());
    }

    std::string line;
    MshData mshData;
    while (std::getline(infile, line)) {
        for (const auto& plugin: this->plugins) {
            if (line == plugin->getSectionKey()) {
                plugin->loadMshData(infile, mshData);

                break;
            }
        }
    }

    if (mshData.version == "") {
        throw std::runtime_error("Could not extract msh version. Check if the file contains a correct .msh file structure.");
    }

    return mshData;
}

void MshDataLoader::registerPlugin(
    std::unique_ptr<MshLoaderPluginInterface> plugin
) {
    plugins.push_back(std::move(plugin));
}
}
