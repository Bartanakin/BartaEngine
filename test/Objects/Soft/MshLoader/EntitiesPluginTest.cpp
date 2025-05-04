#include <Objects/Soft/MshLoader/EntitiesPlugin.h>
#include <gtest/gtest.h>

using namespace Barta::Objects::Soft::MshLoader;

class EntitiesPluginTest: public ::testing::Test {
protected:
    EntitiesPlugin plugin;
    MshData mshData;
};

TEST_F(
    EntitiesPluginTest,
    LoadsSingleSurfaceEntity
) {
    // clang-format off
    std::istringstream input(
        "0 0 1 0\n"                        // n0 (points), n1 (curves), n2 (surfaces), n3 (volumes)
        "10 0.0 2.0 4.0 1.0 3.0 5.0 2 7 8\n" // tag + bbox + 2 physical group tags
    );
    // clang-format on

    plugin.loadMshData(input, mshData);

    const auto& surfaces = mshData.entities[MshData::EntityDimension::SURFACE];
    ASSERT_EQ(surfaces.size(), 1);

    const auto& entity = surfaces[0];
    EXPECT_EQ(entity.tag, 10u);
    EXPECT_FLOAT_EQ(entity.x_min, 0.0f);
    EXPECT_FLOAT_EQ(entity.x_max, 1.0f);
    EXPECT_FLOAT_EQ(entity.y_min, 2.0f);
    EXPECT_FLOAT_EQ(entity.y_max, 3.0f);
    EXPECT_FLOAT_EQ(entity.z_min, 4.0f);
    EXPECT_FLOAT_EQ(entity.z_max, 5.0f);
    ASSERT_EQ(entity.physicalGroupTags.size(), 2);
    EXPECT_EQ(entity.physicalGroupTags[0], 7u);
    EXPECT_EQ(entity.physicalGroupTags[1], 8u);
}

TEST_F(
    EntitiesPluginTest,
    HandlesMultipleSurfaceEntities
) {
    // clang-format off
    std::istringstream input(
        "0 0 2 0\n"
        "20 0 0 0 1 1 1 0\n"
        "30 0 0 0 2 2 2 1 9\n"
    );
    // clang-format on

    plugin.loadMshData(input, mshData);

    const auto& surfaces = mshData.entities[MshData::EntityDimension::SURFACE];
    ASSERT_EQ(surfaces.size(), 2);

    EXPECT_EQ(surfaces[0].tag, 20u);
    EXPECT_TRUE(surfaces[0].physicalGroupTags.empty());

    EXPECT_EQ(surfaces[1].tag, 30u);
    ASSERT_EQ(surfaces[1].physicalGroupTags.size(), 1);
    EXPECT_EQ(surfaces[1].physicalGroupTags[0], 9u);
}

TEST_F(
    EntitiesPluginTest,
    SkipsNonSurfaceEntities
) {
    // clang-format off
    std::istringstream input(
        "2 1 0 2\n"
        "dummy_point\n"
        "dummy_point\n"
        "dummy_curve\n"
        "dummy_volume_1\n"
        "dummy_volume_2\n"
    );
    // clang-format on

    plugin.loadMshData(input, mshData);

    // Only surfaces are stored
    EXPECT_TRUE(mshData.entities[MshData::EntityDimension::SURFACE].empty());
}
