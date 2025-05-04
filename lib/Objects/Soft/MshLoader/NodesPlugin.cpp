#include <Objects/Soft/MshLoader/NodesPlugin.h>

namespace Barta::Objects::Soft::MshLoader {
void NodesPlugin::loadMshData(
    std::istream& in,
    MshData& mshData
) {
    std::string dummy;
    size_t numEntityBlocks, totalNumNodes, minNodeTag, maxNodeTag;
    in >> numEntityBlocks >> totalNumNodes >> minNodeTag >> maxNodeTag;
    std::getline(in, dummy);

    for (size_t i = 0; i < numEntityBlocks; ++i) {
        size_t entityDim, entityTag, parametric, numNodesInBlock;
        in >> entityDim >> entityTag >> parametric >> numNodesInBlock;

        std::vector<size_t> nodeTags(numNodesInBlock);
        for (size_t j = 0; j < numNodesInBlock; ++j) {
            in >> nodeTags[j];
        }

        for (size_t j = 0; j < numNodesInBlock; ++j) {
            float x, y, z;
            in >> x >> y >> z;
            mshData.nodes.emplace_back(nodeTags[j], x, y, z);
        }
    }
}
}
