#include <Objects/Soft/MshLoader/EntitiesPlugin.h>

namespace Barta::Objects::Soft::MshLoader {
void EntitiesPlugin::loadMshData(
    std::istream& in,
    MshData& mshData
) {
    std::string dummy;
    size_t n0, n1, n2, n3;
    in >> n0 >> n1 >> n2 >> n3;
    for (unsigned int i = 0; i < n0; i++) {
        std::getline(in, dummy); // I don't need it so far
    }

    for (unsigned int i = 0; i < n1; i++) {
        std::getline(in, dummy); // I don't need it so far
    }

    for (unsigned int i = 0; i < n2; i++) {
        MshData::Entity entity;
        in >> entity.tag;
        in >> entity.x_min >> entity.y_min >> entity.z_min;
        in >> entity.x_max >> entity.y_max >> entity.z_max;
        size_t numberOfGroups;
        in >> numberOfGroups;
        for (unsigned int j = 0; j < numberOfGroups; j++) {
            unsigned int groupTag;
            in >> groupTag;
            entity.physicalGroupTags.push_back(groupTag);
        }

        mshData.entities[MshData::EntityDimension::SURFACE].push_back(entity);

        std::getline(in, dummy);
    }

    for (unsigned int i = 0; i < n3; i++) {
        std::getline(in, dummy); // I don't need it so far
    }
}
}
