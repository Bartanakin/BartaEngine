#include <Geometrics/BartaShapes/Triangle.h>
#include <pch.h>

namespace Barta {
Triangle::Triangle(
    Point p1,
    Point p2,
    Point p3
):
    p1(p1),
    p2(p2),
    p3(p3) {}

bool Triangle::isWithin(
    Point point
) const noexcept {
    auto u = point - p1;
    auto u2 = p2 - p1;
    auto u3 = p3 - p1;

    auto a11 = u2.squaredNorm();
    auto a22 = u3.squaredNorm();
    auto a12 = -u3.dot(u2);

    auto determinant_inv = 1.f / (a11 * a22 - a12 * a12);

    auto testVec = determinant_inv * Vector(u.dot(u2), u.dot(u3));
    auto c1 = Vector(a22, a12).dot(testVec);
    auto c2 = Vector(a12, a11).dot(testVec);

    return c1 >= 0.f && c2 >= 0.f && c1 + c2 <= 1.f;
}
}
