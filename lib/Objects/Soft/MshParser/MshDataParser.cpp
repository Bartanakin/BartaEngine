#include <Objects/Soft/MshParser/MshDataParser.h>
#include "Geometrics/BartaShapes/Triangle.h"
#include <Objects/Soft/Mesh.h>
#include <Objects/Soft/MshParser/MshDataParserInterface.h>

namespace Barta::Objects::Soft::MshParser {
Mesh MshDataParser::parse(
    const MshParser::MshData& mshData
) const {
    std::vector<Node> nodes;
    NodalVectorType nodePositions(3 * mshData.nodes.size());
    for (size_t i = 0; i < mshData.nodes.size(); ++i) {
        DynamicsDTO dynamics;
        dynamics.massCenter = {mshData.nodes[i].x, mshData.nodes[i].y, mshData.nodes[i].z};
        nodePositions[3 * i] = mshData.nodes[i].x;
        nodePositions[3 * i + 1] = mshData.nodes[i].y;
        nodePositions[3 * i + 2] = mshData.nodes[i].z;

        nodes.emplace_back(DynamicsDTOCollection{dynamics}, mshData.nodes[i].tag, false);
    }

    return {std::move(nodes), {}};
}
}
