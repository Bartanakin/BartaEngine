#include <pch.h>
#include <gtest/gtest.h>
#include <Hitbox/TriangleAggregateHitbox.h>

using namespace Barta::Hitbox;
TEST(TriangleAggregateHitboxTest, IntersectsSingleTriangle) {
    std::vector<Barta::Triangle> triangles = {
        {
            {0, 0, 0},
            {1, 0, 0},
            {0, 1, 0}
        }
    };
    TriangleAggregateHitbox hitbox({triangles, {}});

    Barta::Ray ray{{0.25f, 0.25f, -1.0f}, {0, 0, 1}};

    auto intersections = hitbox.intersectsWithRay(ray);
    ASSERT_EQ(intersections.size(), 1);
    EXPECT_NEAR(intersections[0], 1.0f, 1e-5f);
}

TEST(TriangleAggregateHitboxTest, NoIntersectionWithAnyTriangle) {
    std::vector<Barta::Triangle> triangles = {
        {{0, 0, 0}, {1, 0, 0}, {0, 1, 0}},
        {{1, 1, 1}, {2, 1, 1}, {1, 2, 1}}
    };
    TriangleAggregateHitbox hitbox({triangles, {}});

    Barta::Ray ray{{5, 5, -1}, {0, 0, 1}};
    auto intersections = hitbox.intersectsWithRay(ray);
    EXPECT_TRUE(intersections.empty());
}

TEST(TriangleAggregateHitboxTest, IntersectsMultipleTriangles) {
    std::vector<Barta::Triangle> triangles = {
        {{-1, -1, 0}, {1, -1, 0}, {0, 1, 0}},
        {{-1, -1, 2}, {1, -1, 2}, {0, 1, 2}}
    };
    TriangleAggregateHitbox hitbox({triangles, {}});

    Barta::Ray ray{{0, 0, -1}, {0, 0, 1}};
    auto intersections = hitbox.intersectsWithRay(ray);
    ASSERT_EQ(intersections.size(), 2);
    EXPECT_NEAR(intersections[0], 1.0f, 1e-5f);
    EXPECT_NEAR(intersections[1], 3.0f, 1e-5f);
}

TEST(TriangleAggregateHitboxTest, IgnoresNegativeIntersections) {
    std::vector<Barta::Triangle> triangles = {
        {{0, 0, 0}, {1, 0, 0}, {0, 1, 0}}
    };
    TriangleAggregateHitbox hitbox({std::move(triangles), {}});

    Barta::Ray ray{{0.25f, 0.25f, 1.0f}, {0, 0, -1}}; // From above, toward triangle front
    auto intersections = hitbox.intersectsWithRay(ray);
    ASSERT_EQ(intersections.size(), 1);
    EXPECT_NEAR(intersections[0], 1.0f, 1e-5f);

    Barta::Ray reverseRay{{0.25f, 0.25f, -1.0f}, {0, 0, -1}}; // Away from triangle
    auto reverseIntersections = hitbox.intersectsWithRay(reverseRay);
    EXPECT_TRUE(reverseIntersections.empty());
}

