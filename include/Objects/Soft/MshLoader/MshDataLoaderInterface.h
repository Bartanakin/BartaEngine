#pragma once
#include "MshData.h"
#include <Objects/Soft/Mesh.h>

namespace Barta::Objects::Soft::MshLoader {
class MshDataLoaderInterface {
public:
    virtual ~MshDataLoaderInterface() = default;

    virtual MshData loadMshDataFromFile(const std::filesystem::path& filePath) const = 0;
};

}
