#pragma once
#include <pch.h>

namespace Barta::Objects::Soft::MshLoader {

struct MshData {
    enum class ElementType {
        TRIANGLE = 2,
        TETRAHEDRON = 4
    };

    enum class EntityDimension {
        POINT = 0,
        LINE = 1,
        SURFACE = 2,
        VOLUME = 3
    };

    struct PhysicalGroup {
        unsigned int tag;
        unsigned int dim;
        std::string name;
    };

    struct Entity {
        unsigned int tag;
        float x_min, y_min, z_min;
        float x_max, y_max, z_max;
        std::vector<unsigned int> physicalGroupTags;
    };

    struct Node3D {
        unsigned int tag;
        float x, y, z;
    };

    struct TetrahedralElement {
        std::array<unsigned int, 4> nodeTags;
    };

    struct TriangleElement {
        unsigned int entityTag;
        std::array<unsigned int, 3> nodeTags;
    };

    std::string version;
    std::vector<PhysicalGroup> physicalGroups;
    std::map<EntityDimension, std::vector<Entity>> entities;
    std::vector<Node3D> nodes;
    std::vector<TetrahedralElement> tetrahedralElements;
    std::vector<TriangleElement> triangleElements;
};
}
