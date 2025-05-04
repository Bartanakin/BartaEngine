#include <Dynamics/SoftBody/SoftBodyDynamicsInterface.h>

namespace Barta::Dynamics::SoftBody {
void SoftBodyDynamicsInterface::emplace12Matrix(
    const Utils::Matrix12Type& m12,
    const std::array<unsigned int, 4>& nodeIndices,
    StiffnessMatrixType& stiffnessMatrix,
    unsigned int block3x3Count
) {
    // std::cout << m12    << std::endl << std::endl;
    for (unsigned int i = 0; i < 4; i++) {
        if (nodeIndices[i] >= block3x3Count) {
            continue;
        }

        for (unsigned int j = 0; j < 4; j++) {
            if (nodeIndices[j] >= block3x3Count) {
                continue;
            }

            stiffnessMatrix.block(3 * nodeIndices[i], 3 * nodeIndices[j], 3, 3) += m12.block<3, 3>(3 * i, 3 * j);
        }
    }
}
}
