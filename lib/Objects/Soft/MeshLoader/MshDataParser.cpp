#include <Objects/Soft/MeshLoader/MshDataParser.h>
#include "Geometrics/BartaShapes/Triangle.h"
#include "Geometrics/ConvexFactor.h"

namespace Barta::Objects::Soft::MeshLoader {
Mesh MshDataParser::parse(
    const MshData& mshData
) const {
    std::map<size_t, size_t> nodeTagToIndex; // maps Gmsh node ID → index in vector
    std::vector<Node> nodes;
    std::vector<TetrahedralElement> tetrahedralElements;
    for (size_t i = 0; i < mshData.nodes.size(); ++i) {
        nodeTagToIndex[mshData.nodes[i].tag] = i;

        DynamicsDTO dynamics;
        dynamics.massCenter = {mshData.nodes[i].x, mshData.nodes[i].y, mshData.nodes[i].z};
        nodes.emplace_back(std::to_string(mshData.nodes[i].tag), DynamicsDTOCollection{dynamics}, false);
    }

    for (size_t i = 0; i < mshData.elements.size(); ++i) {
        if (mshData.elements[i].type != MshData::ElementType::TETRAHEDRON) {
            continue;
        }

        auto nodeTags = mshData.elements[i].nodeIndices;
        std::array<Point, 4> positions;
        for (size_t k = 0; k < 4; ++k) {
            positions[k] = nodes[nodeTagToIndex[nodeTags[k]]].dynamicsDTOCollection[DynamicsDTOIteration::CURRENT].massCenter;
        }

        Point tetrahedralCenter = ConvexFactor::baricentricCombination(positions);
        auto faceIndices = TetrahedralElement::FACE_INDICES_CONTAINER[0];
        auto normal = Triangle{positions[faceIndices[0]], positions[faceIndices[1]], positions[faceIndices[2]]}.getNormal();

        Point faceCenter = ConvexFactor::baricentricCombination(
            std::initializer_list{positions[faceIndices[0]], positions[faceIndices[1]], positions[faceIndices[2]]}
        );

        if ((tetrahedralCenter - faceCenter).dot(normal) > 0.) {
            std::swap(nodeTags[1], nodeTags[2]);
        }

        tetrahedralElements.emplace_back(
            nodes[nodeTagToIndex[nodeTags[0]]],
            nodes[nodeTagToIndex[nodeTags[1]]],
            nodes[nodeTagToIndex[nodeTags[2]]],
            nodes[nodeTagToIndex[nodeTags[3]]]
        );
    }

    return Mesh(std::move(nodes), std::move(tetrahedralElements));
}
}
