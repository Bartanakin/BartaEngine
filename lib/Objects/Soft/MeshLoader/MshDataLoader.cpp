#include <Objects/Soft/MeshLoader/MshDataLoader.h>

namespace Barta::Objects::Soft::MeshLoader {
MshData MshDataLoader::loadMshDataFromFile(
    const std::filesystem::path& filePath
) const {
    std::ifstream infile(filePath.string());
    if (!infile) {
        throw std::runtime_error("Failed to open file: " + filePath.string());
    }

    std::string line;
    unsigned int nextNodeIndex = 0;
    MshData mshData;
    while (std::getline(infile, line)) {
        if (line == "$MeshFormat") {
            std::string version;
            size_t s1, s2;
            infile >> version >> s1 >> s2;

            if (std::find(MshDataLoader::ALLOWED_VERSIONS.begin(), MshDataLoader::ALLOWED_VERSIONS.end(), version)
                == MshDataLoader::ALLOWED_VERSIONS.end()) {
                throw std::runtime_error("The msh file has an incompatible version: " + version);
            }

            mshData.version = version;

            std::getline(infile, line);
        }

        if (line == "$Nodes") {
            size_t numEntityBlocks, totalNumNodes, minNodeTag, maxNodeTag;
            infile >> numEntityBlocks >> totalNumNodes >> minNodeTag >> maxNodeTag;
            std::getline(infile, line);

            for (size_t i = 0; i < numEntityBlocks; ++i) {
                size_t entityDim, entityTag, parametric, numNodesInBlock;
                infile >> entityDim >> entityTag >> parametric >> numNodesInBlock;

                std::vector<size_t> nodeTags(numNodesInBlock);
                for (size_t j = 0; j < numNodesInBlock; ++j) {
                    infile >> nodeTags[j];
                    ++nextNodeIndex;
                }

                for (size_t j = 0; j < numNodesInBlock; ++j) {
                    float x, y, z;
                    infile >> x >> y >> z;
                    mshData.nodes.emplace_back(nodeTags[j], x, y, z);
                }
            }
        }

        else if (line == "$Elements") {
            size_t numEntityBlocks, totalNumElements, minElemTag, maxElemTag;
            infile >> numEntityBlocks >> totalNumElements >> minElemTag >> maxElemTag;
            std::getline(infile, line);

            for (size_t i = 0; i < numEntityBlocks; ++i) {
                size_t entityDim, entityTag, elementType, numElemsInBlock;
                infile >> entityDim >> entityTag >> elementType >> numElemsInBlock;
                std::getline(infile, line);

                if (elementType != 4) {
                    for (size_t j = 0; j < numElemsInBlock; ++j) {
                        std::getline(infile, line);
                    }

                    continue;
                }

                for (size_t j = 0; j < numElemsInBlock; ++j) {
                    std::array<unsigned int, 4> nodeTags = {};
                    infile >> line >> nodeTags[0] >> nodeTags[1] >> nodeTags[2] >> nodeTags[3];
                    mshData.elements.emplace_back(MshData::ElementType::TETRAHEDRON, std::move(nodeTags));
                }
            }
        }
    }

    if (mshData.version == "") {
        throw std::runtime_error("Could not extract msh version. Check if the file contains a correct .msh file structure.");
    }

    return mshData;
}
}
