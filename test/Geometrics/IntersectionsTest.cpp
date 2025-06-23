#include "Geometrics/Intersections.h"
#include <Hitbox/TriangleAggregateHitbox.h>
#include <gtest/gtest.h>
#include <pch.h>

using namespace Barta;

TEST(RayAndTriangleTest, IntersectsInside) {
    Barta::Ray ray{{0.5, 0.5, 2}, {0, 0, -1}};
    Barta::Triangle tri{{0, 0, 0}, {2, 0, 0}, {0, 2, 0}};

    auto result = Barta::Intersections::rayAndTriangle(ray, tri);
    ASSERT_EQ(result.size(), 1);
    EXPECT_NEAR(result[0], 2.0f, 1e-5f);
}

TEST(RayAndTriangleTest, MissesTriangle) {
    Barta::Ray ray{{1.5f, 1.5f, -1.0f}, {0.0f, 0.0f, 1.0f}};
    Barta::Triangle tri{{0, 0, 0}, {1, 0, 0}, {0, 1, 0}};

    auto result = Barta::Intersections::rayAndTriangle(ray, tri);
    EXPECT_TRUE(result.empty());
}

TEST(RayAndTriangleTest, HitsEdge) {
    Barta::Ray ray{{0.5f, 0.0f, -1.0f}, {0.0f, 0.0f, 1.0f}};
    Barta::Triangle tri{{0, 0, 0}, {1, 0, 0}, {0, 1, 0}};

    auto result = Barta::Intersections::rayAndTriangle(ray, tri);
    ASSERT_EQ(result.size(), 1);
    EXPECT_NEAR(result[0], 1.0f, 1e-5f);
}

TEST(RayAndTriangleTest, RayParallelNoIntersection) {
    Barta::Ray ray{{0.5f, 0.5f, 1.0f}, {1.0f, 0.0f, 0.0f}};
    Barta::Triangle tri{{0, 0, 0}, {1, 0, 0}, {0, 1, 0}};

    auto result = Barta::Intersections::rayAndTriangle(ray, tri);
    EXPECT_TRUE(result.empty());
}

