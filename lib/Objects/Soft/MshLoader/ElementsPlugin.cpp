#include <Objects/Soft/MshLoader/ElementsPlugin.h>

namespace Barta::Objects::Soft::MshLoader {
void ElementsPlugin::loadMshData(
    std::istream& in,
    MshData& mshData
) {
    std::string dummy;
    size_t numEntityBlocks, totalNumElements, minElemTag, maxElemTag;
    in >> numEntityBlocks >> totalNumElements >> minElemTag >> maxElemTag;
    std::getline(in, dummy);

    for (size_t i = 0; i < numEntityBlocks; ++i) {
        size_t entityDim, entityTag, elementType, numElemsInBlock;
        in >> entityDim >> entityTag >> elementType >> numElemsInBlock;
        std::getline(in, dummy);

        if (elementType == static_cast<size_t>(MshData::ElementType::TRIANGLE)) {
            for (size_t j = 0; j < numElemsInBlock; ++j) {
                unsigned int elementTag;
                std::array<unsigned int, 3> nodeTags = {};
                in >> elementTag >> nodeTags[0] >> nodeTags[1] >> nodeTags[2];

                mshData.triangleElements.emplace_back(entityTag, nodeTags);
            }
        } else if (elementType == static_cast<size_t>(MshData::ElementType::TETRAHEDRON)) {
            for (size_t j = 0; j < numElemsInBlock; ++j) {
                unsigned int elementTag;
                std::array<unsigned int, 4> nodeTags = {};
                in >> elementTag >> nodeTags[0] >> nodeTags[1] >> nodeTags[2] >> nodeTags[3];

                mshData.tetrahedralElements.emplace_back(nodeTags);
            }
        } else {
            for (size_t j = 0; j < numElemsInBlock; ++j) {
                std::getline(in, dummy);
            }
        }
    }
}
}
