#include <Objects/Soft/MshLoader/MeshFormatPlugin.h>

namespace Barta::Objects::Soft::MshLoader {
void MeshFormatPlugin::loadMshData(
    std::istream& in,
    MshData& mshData
) {
    std::string version;
    size_t s1, s2;
    in >> version >> s1 >> s2;

    if (std::ranges::find(MeshFormatPlugin::ALLOWED_VERSIONS, version) == MeshFormatPlugin::ALLOWED_VERSIONS.end()) {
        throw std::runtime_error("The msh file has an incompatible version: " + version);
    }

    mshData.version = version;

    std::string dummy;
    std::getline(in, dummy);
}
}
