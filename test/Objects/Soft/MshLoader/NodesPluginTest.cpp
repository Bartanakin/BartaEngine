#include <Objects/Soft/MshLoader/NodesPlugin.h>
#include <Objects/Soft/MshLoader/MshData.h>
#include <gtest/gtest.h>
#include <sstream>

using namespace Barta::Objects::Soft::MshLoader;

TEST(
    NodesPluginTest,
    LoadsSingleBlockWithTwoNodes
) {
    NodesPlugin plugin;
    MshData mshData;

    // clang-format off
    std::istringstream input(
        "1 2 1 2\n"        // numBlocks totalNodes minTag maxTag
        "3 7 0 2\n"        // entityDim entityTag parametric numNodes
        "101 102\n"        // node tags
        "1.0 2.0 3.0\n"    // coordinates for node 101
        "4.0 5.0 6.0\n"    // coordinates for node 102
    );
    // clang-format on

    plugin.loadMshData(input, mshData);

    ASSERT_EQ(mshData.nodes.size(), 2);

    EXPECT_EQ(mshData.nodes[0].tag, 101);
    EXPECT_FLOAT_EQ(mshData.nodes[0].x, 1.0f);
    EXPECT_FLOAT_EQ(mshData.nodes[0].y, 2.0f);
    EXPECT_FLOAT_EQ(mshData.nodes[0].z, 3.0f);

    EXPECT_EQ(mshData.nodes[1].tag, 102);
    EXPECT_FLOAT_EQ(mshData.nodes[1].x, 4.0f);
    EXPECT_FLOAT_EQ(mshData.nodes[1].y, 5.0f);
    EXPECT_FLOAT_EQ(mshData.nodes[1].z, 6.0f);
}

TEST(
    NodesPluginTest,
    HandlesMultipleEntityBlocks
) {
    NodesPlugin plugin;
    MshData mshData;

    // clang-format off
    std::istringstream input(
        "2 3 10 12\n"
        "2 5 0 1\n"
        "10\n"
        "0.0 0.0 0.0\n"
        "3 8 0 2\n"
        "11 12\n"
        "1.0 1.0 1.0\n"
        "2.0 2.0 2.0\n"
    );
    // clang-format on

    plugin.loadMshData(input, mshData);

    ASSERT_EQ(mshData.nodes.size(), 3);

    EXPECT_EQ(mshData.nodes[0].tag, 10);
    EXPECT_FLOAT_EQ(mshData.nodes[1].x, 1.0f);
    EXPECT_EQ(mshData.nodes[2].tag, 12);
}

TEST(
    NodesPluginTest,
    EmptyInputDoesNotThrow
) {
    NodesPlugin plugin;
    MshData mshData;

    std::istringstream input("0 0 0 0\n");

    EXPECT_NO_THROW(plugin.loadMshData(input, mshData));
    EXPECT_TRUE(mshData.nodes.empty());
}
