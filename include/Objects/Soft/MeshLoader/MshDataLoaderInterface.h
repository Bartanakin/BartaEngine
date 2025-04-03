#pragma once
#include <Objects/Soft/Mesh.h>
#include <Objects/Soft/MeshLoader/MshData.h>

namespace Barta::Objects::Soft::MeshLoader {
class MshDataLoaderInterface {
public:
    virtual ~MshDataLoaderInterface() = default;

    virtual MshData loadMshDataFromFile(const std::filesystem::path& filePath) const = 0;
};

}
