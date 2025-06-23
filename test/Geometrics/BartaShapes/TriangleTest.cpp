#include <pch.h>
#include <gtest/gtest.h>
#include <Geometrics/BartaShapes/TriangleSurface.h>

using namespace Barta;

class TriangleClosestPointTest : public ::testing::Test {
protected:
    Triangle triangle;

    void SetUp() override {
        this->triangle = {
            {0, 0, 0},
            {1, 0, 0},
            {0, 1, 0}
        };
    }
};

TEST_F(TriangleClosestPointTest, PointAtAVertex) {
    Point testPoint = Point(0, 0, 0);
    Point result = triangle.closestPoint(testPoint);
    EXPECT_TRUE(result.isApprox(Point(0, 0, 0)));
}

TEST_F(TriangleClosestPointTest, PointClosestToAVertex) {
    Point testPoint = Point(1.5, -0.5, 0);
    Point result = triangle.closestPoint(testPoint);
    EXPECT_TRUE(result.isApprox(Point(1, 0, 0)));
}

TEST_F(TriangleClosestPointTest, PointAtAnEdge) {
    Point testPoint = Point(0.5, 0, 0);
    Point expected = Point(0.5, 0.0, 0);
    Point result = triangle.closestPoint(testPoint);
    EXPECT_TRUE(result.isApprox(expected));
}

TEST_F(TriangleClosestPointTest, PointClosestToInteriorOfAnEdge) {
    Point testPoint = Point(0.5, -1.0, 0);
    Point expected = Point(0.5, 0.0, 0);
    Point result = triangle.closestPoint(testPoint);
    EXPECT_TRUE(result.isApprox(expected));
}

TEST_F(TriangleClosestPointTest, PointClosestToInteriorOfAnEdge2) {
    Point testPoint = Point(1, 1, 0);
    Point expected = Point(0.5, 0.5, 0);
    Point result = triangle.closestPoint(testPoint);
    EXPECT_TRUE(result.isApprox(expected));
}

TEST_F(TriangleClosestPointTest, PointInsideTheTriangle) {
    Point testPoint = Point(0.25, 0.25, 0.0);
    Point expected = Point(0.25, 0.25, 0.0);
    Point result = triangle.closestPoint(testPoint);
    EXPECT_TRUE(result.isApprox(expected));
}

TEST_F(TriangleClosestPointTest, PointAboveTheTriangle) {
    Point testPoint = Point(0.25, 0.25, 1.0);
    Point expected = Point(0.25, 0.25, 0.0);
    Point result = triangle.closestPoint(testPoint);
    EXPECT_TRUE(result.isApprox(expected));
}

TEST_F(TriangleClosestPointTest, GetConvexCoordinates_CenterOfTriangle) {
    Point X = {1.0 / 3, 1.0 / 3, 0};

    auto bary = this->triangle.getConvexCoordinates(X);

    EXPECT_NEAR(bary[0], 1.0 / 3, 1e-6);
    EXPECT_NEAR(bary[1], 1.0 / 3, 1e-6);
    EXPECT_NEAR(bary[2], 1.0 / 3, 1e-6);
}

TEST_F(TriangleClosestPointTest, GetConvexCoordinates_Vertex) {
    auto bary = this->triangle.getConvexCoordinates(this->triangle.p1);

    EXPECT_NEAR(bary[0], 1.0, 1e-6);
    EXPECT_NEAR(bary[1], 0.0, 1e-6);
    EXPECT_NEAR(bary[2], 0.0, 1e-6);
}