#include <Dynamics/SoftBody/SoftBodyDynamicsInterface.h>
#include <gtest/gtest.h>
#include <pch.h>

using namespace Barta::Dynamics::SoftBody;

TEST(
    SoftBodyDynamicsInterface,
    Emplace12Matrix
) {
    std::array<unsigned int, 4> nodeIndices = {4, 3, 1, 2};
    StiffnessMatrixType stiffnessMatrix = StiffnessMatrixType::Zero(12, 12);
    Barta::Utils::Matrix12Type m12;
    // clang-format off
    m12 <<  1, 1, 1,            10, 10, 10,         100, 100, 100,      -111, -111, -111,
            1, 1, 1,            10, 10, 10,         100, 100, 100,      -111, -111, -111,
            1, 1, 1,            10, 10, 10,         100, 100, 100,      -111, -111, -111,

            2, 2, 2,            20, 20, 20,         200, 200, 200,      -222, -222, -222,
            2, 2, 2,            20, 20, 20,         200, 200, 200,      -222, -222, -222,
            2, 2, 2,            20, 20, 20,         200, 200, 200,      -222, -222, -222,

            4, 4, 4,            40, 40, 40,         400, 400, 400,      -444, -444, -444,
            4, 4, 4,            40, 40, 40,         400, 400, 400,      -444, -444, -444,
            4, 4, 4,            40, 40, 40,         400, 400, 400,      -444, -444, -444,

            -111, -111, -111,   -222, -222, -222,   -444, -444, -444,   777, 777, 777,
            -111, -111, -111,   -222, -222, -222,   -444, -444, -444,   777, 777, 777,
            -111, -111, -111,   -222, -222, -222,   -444, -444, -444,   777, 777, 777;
    // clang-format on

    StiffnessMatrixType expected = StiffnessMatrixType::Zero(12, 12);
    // clang-format off
    expected << 0, 0, 0,        0, 0, 0,            0, 0, 0,            0, 0, 0,
                0, 0, 0,        0, 0, 0,            0, 0, 0,            0, 0, 0,
                0, 0, 0,        0, 0, 0,            0, 0, 0,            0, 0, 0,

                0, 0, 0,        400, 400, 400,      -444, -444, -444,   40, 40, 40,
                0, 0, 0,        400, 400, 400,      -444, -444, -444,   40, 40, 40,
                0, 0, 0,        400, 400, 400,      -444, -444, -444,   40, 40, 40,

                0, 0, 0,        -444, -444, -444,   777, 777, 777,      -222, -222, -222,
                0, 0, 0,        -444, -444, -444,   777, 777, 777,      -222, -222, -222,
                0, 0, 0,        -444, -444, -444,   777, 777, 777,      -222, -222, -222,

                0, 0, 0,        200, 200, 200,      -222, -222, -222,   20, 20, 20,
                0, 0, 0,        200, 200, 200,      -222, -222, -222,   20, 20, 20,
                0, 0, 0,        200, 200, 200,      -222, -222, -222,   20, 20, 20,
        // clang-format on

        SoftBodyDynamicsInterface::emplace12Matrix(m12, nodeIndices, stiffnessMatrix, 4);

    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 12; ++j) {
            EXPECT_FLOAT_EQ(stiffnessMatrix(i, j), expected(i, j));
        }
    }
}
