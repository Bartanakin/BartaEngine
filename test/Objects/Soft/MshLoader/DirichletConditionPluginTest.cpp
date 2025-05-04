#include <Objects/Soft/MshLoader/DirichletConditionPlugin.h>
#include <gtest/gtest.h>

using namespace Barta::Objects::Soft::MshLoader;

class DirichletConditionPluginTest: public ::testing::Test {
protected:
    DirichletConditionPlugin plugin;
    MshData mshData;
};

TEST_F(
    DirichletConditionPluginTest,
    LoadsSingleDirichletGroup
) {
    std::istringstream input("1\n1 42 left_wall\n");

    plugin.loadMshData(input, mshData);

    ASSERT_EQ(mshData.physicalGroups.size(), 1);
    const auto& group = mshData.physicalGroups[0];

    EXPECT_EQ(group.dim, 1u);
    EXPECT_EQ(group.tag, 42u);
    EXPECT_EQ(group.name, "left_wall");
}

TEST_F(
    DirichletConditionPluginTest,
    LoadsMultipleGroups
) {
    std::istringstream input("2\n2 1 top\n1 2 bottom\n");

    plugin.loadMshData(input, mshData);

    ASSERT_EQ(mshData.physicalGroups.size(), 2);

    EXPECT_EQ(mshData.physicalGroups[0].name, "top");
    EXPECT_EQ(mshData.physicalGroups[1].name, "bottom");
}

TEST_F(
    DirichletConditionPluginTest,
    HandlesEmptyInput
) {
    std::istringstream input("0\n");

    EXPECT_NO_THROW(plugin.loadMshData(input, mshData));
    EXPECT_TRUE(mshData.physicalGroups.empty());
}
