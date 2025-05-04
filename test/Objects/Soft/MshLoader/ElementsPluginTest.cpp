#include <Objects/Soft/MshLoader/ElementsPlugin.h>
#include <gtest/gtest.h>

using namespace Barta::Objects::Soft::MshLoader;

class ElementsPluginTest: public ::testing::Test {
protected:
    ElementsPlugin plugin;
    MshData mshData;
};

// These values should match your enum in MshData
constexpr size_t TRIANGLE_TYPE = static_cast<size_t>(MshData::ElementType::TRIANGLE);
constexpr size_t TETRAHEDRON_TYPE = static_cast<size_t>(MshData::ElementType::TETRAHEDRON);

TEST_F(
    ElementsPluginTest,
    ParsesSingleTriangleElement
) {
    // clang-format off
    std::istringstream input(
        "1 1 101 101\n"       // numBlocks, totalElements, minTag, maxTag
        "2 5 " + std::to_string(TRIANGLE_TYPE) + " 1\n"
        "101 1 2 3\n"
    );
    // clang-format on

    plugin.loadMshData(input, mshData);

    ASSERT_EQ(mshData.triangleElements.size(), 1);
    EXPECT_EQ(mshData.triangleElements[0].entityTag, 5u); // entityTag
    EXPECT_EQ(mshData.triangleElements[0].nodeTags[0], 1u);
    EXPECT_EQ(mshData.triangleElements[0].nodeTags[1], 2u);
    EXPECT_EQ(mshData.triangleElements[0].nodeTags[2], 3u);
}

TEST_F(
    ElementsPluginTest,
    ParsesSingleTetrahedronElement
) {
    // clang-format off
    std::istringstream input(
        "1 1 201 201\n"
        "3 7 " + std::to_string(TETRAHEDRON_TYPE) + " 1\n"
        "201 4 5 6 7\n"
    );
    // clang-format on

    plugin.loadMshData(input, mshData);

    ASSERT_EQ(mshData.tetrahedralElements.size(), 1);
    EXPECT_EQ(mshData.tetrahedralElements[0].nodeTags[0], 4u);
    EXPECT_EQ(mshData.tetrahedralElements[0].nodeTags[1], 5u);
    EXPECT_EQ(mshData.tetrahedralElements[0].nodeTags[2], 6u);
    EXPECT_EQ(mshData.tetrahedralElements[0].nodeTags[3], 7u);
}

TEST_F(
    ElementsPluginTest,
    SkipsUnsupportedElementTypes
) {
    std::istringstream input("1 1 1 1\n" "1 1 999 1\n" // Unknown element type 999
                             "1 8 9 10 11\n");

    plugin.loadMshData(input, mshData);

    EXPECT_TRUE(mshData.triangleElements.empty());
    EXPECT_TRUE(mshData.tetrahedralElements.empty());
}

TEST_F(
    ElementsPluginTest,
    HandlesMultipleBlocks
) {
    std::ostringstream oss;
    // clang-format off
    oss << "2 2 1 2\n"
        << "2 1 " << TRIANGLE_TYPE << " 1\n"
        << "1 10 11 12\n"
        << "3 2 " << TETRAHEDRON_TYPE << " 1\n"
        << "2 20 21 22 23\n";
    // clang-format on

    std::istringstream input(oss.str());
    plugin.loadMshData(input, mshData);

    ASSERT_EQ(mshData.triangleElements.size(), 1);
    ASSERT_EQ(mshData.tetrahedralElements.size(), 1);
}
