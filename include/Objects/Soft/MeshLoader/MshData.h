#pragma once
#include <pch.h>

namespace Barta::Objects::Soft::MeshLoader {

struct MshData {
    enum class ElementType {
        TETRAHEDRON = 4
    };

    struct Node3D {
        unsigned int tag;
        float x, y, z;
    };

    struct Element {
        ElementType type;
        std::array<unsigned int, 4> nodeIndices;
    };

    std::string version;
    std::vector<Node3D> nodes;
    std::vector<Element> elements;
};
}
