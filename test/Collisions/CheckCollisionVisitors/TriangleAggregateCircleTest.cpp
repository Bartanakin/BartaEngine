#include <Collisions/CheckCollisionVisitors/TriangleAggregateCircle.h>
#include "Hitbox/TriangleAggregateHitbox.h"
#include <gtest/gtest.h>
#include <pch.h>

using namespace Barta::Collisions::CheckCollisionVisitors;


TEST(TriangleAggregateHitboxTest, SingleTriangleBoundingOBB) {
    std::vector<Barta::Triangle> triangles = {{{0, 0, 0}, {1, 0, 0}, {0, 1, 0}}};
    Barta::Hitbox::TriangleAggregateHitbox hitbox({triangles, {}});

    auto obb = hitbox.getBoundingOBB();
    auto expectedVertex = Barta::Point{0, 0, 0};
    auto expectedWidthHeight = Barta::Vector{1, 1, 0};
    EXPECT_EQ(obb.getFirstVertex(), expectedVertex);
    EXPECT_EQ(obb.getWidthHeight(), expectedWidthHeight);
}

TEST(TriangleAggregateHitboxTest, MultipleTrianglesBoundingOBB) {
    std::vector<Barta::Triangle> triangles = {
        {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}},
        {{-1, -2, -3}, {0, 0, 0}, {2, 2, 2}},
        {{-10, 2, 6}, {0, 0, 0}, {2, 2, 2}}
    };
    Barta::Hitbox::TriangleAggregateHitbox hitbox({triangles, {}});

    auto obb = hitbox.getBoundingOBB();
    auto expectedVertex = Barta::Point{-10, -2, -3};
    auto expectedWidthHeight = Barta::Vector{17, 10, 12};
    EXPECT_EQ(obb.getFirstVertex(), expectedVertex);
    EXPECT_EQ(obb.getWidthHeight(), expectedWidthHeight);
}
