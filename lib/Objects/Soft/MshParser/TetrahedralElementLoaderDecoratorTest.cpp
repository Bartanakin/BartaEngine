#include <Objects/Soft/MshParser/TetrahedralElementLoaderDecorator.h>
#include "Geometrics/BartaShapes/Triangle.h"
#include "Geometrics/ConvexFactor.h"

namespace Barta::Objects::Soft::MshParser {
TetrahedralElementLoaderDecorator::TetrahedralElementLoaderDecorator(
    MshDataParserInterface& decorated
) noexcept:
    decorated(decorated) {}

Mesh TetrahedralElementLoaderDecorator::parse(
    const MshData& mshData
) const {
    auto mesh = this->decorated.parse(mshData);

    std::map<size_t, size_t> nodeTagToIndex; // maps Gmsh node ID → index in vector
    std::vector<TetrahedralElement> tetrahedralElements;
    for (size_t i = 0; i < mesh.nodes.size(); ++i) {
        nodeTagToIndex[mesh.nodes[i].tag] = i;
    }

    for (auto tetrahedralElement: mshData.tetrahedralElements) {
        auto nodeTags = tetrahedralElement.nodeTags;
        std::array<Point, 4> positions;
        for (size_t k = 0; k < 4; ++k) {
            positions[k] = mesh.nodes[nodeTagToIndex[nodeTags[k]]].dynamicsDTOCollection[DynamicsDTOIteration::CURRENT].massCenter;
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

        // clang-format off
        tetrahedralElements.emplace_back(
            mesh.nodes,
            nodeTagToIndex[nodeTags[0]],
            nodeTagToIndex[nodeTags[1]],
            nodeTagToIndex[nodeTags[2]],
            nodeTagToIndex[nodeTags[3]]
        );
        // clang-format on
    }

    mesh.elements = tetrahedralElements;

    return mesh;
}
}
