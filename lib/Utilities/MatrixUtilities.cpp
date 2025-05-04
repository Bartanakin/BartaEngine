#include <Utilities/MatrixUtilities.h>

namespace Barta::Utils {
Matrix12Type create12MatrixFrom9MatrixAndThirdNewtonLaw(
    const Matrix9Type& m9
) {
    Matrix12Type m12 = Matrix12Type::Zero();
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            auto currBlock = m9.block<3, 3>(3 * i, 3 * j);
            // 9x9 left top
            m12.block<3, 3>(3 * i, 3 * j) += currBlock;
            // 3x9 left bottom
            m12.block<3, 3>(3 * 3, 3 * j) -= currBlock;
            // 9x3 right top
            m12.block<3, 3>(3 * i, 3 * 3) -= currBlock;
            // 3x3 right bottom
            m12.block<3, 3>(3 * 3, 3 * 3) += currBlock;
        }
    }

    return m12;
}
}
