#include <Objects/Soft/MshLoader/DirichletConditionPlugin.h>

namespace Barta::Objects::Soft::MshLoader {
void DirichletConditionPlugin::loadMshData(
    std::istream& in,
    MshData& mshData
) {
    size_t n;
    in >> n;
    std::string dummy;
    for (size_t i = 0; i < n; ++i) {
        MshData::PhysicalGroup physicalGroup;
        in >> physicalGroup.dim;
        in >> physicalGroup.tag;
        in >> physicalGroup.name;

        mshData.physicalGroups.push_back(std::move(physicalGroup));

        std::getline(in, dummy);
    }
}
}
