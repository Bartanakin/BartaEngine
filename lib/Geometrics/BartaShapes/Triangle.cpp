#include <Geometrics/BartaShapes/Triangle.h>
#include <pch.h>

Barta::Triangle::Triangle(
    Vector2f p1,
    Vector2f p2,
    Vector2f p3
):
    p1(p1),
    p2(p2),
    p3(p3) {}

bool Barta::Triangle::isWithin(
    Vector2f point
) const noexcept {
    auto u = point - p1;
    auto u2 = p2 - p1;
    auto u3 = p3 - p1;

    auto a11 = u2.normSquare();
    auto a22 = u3.normSquare();
    auto a12 = -u3 * u2;

    auto determinant_inv = 1.f / (a11 * a22 - a12 * a12);

    auto testVec = determinant_inv * Vector2f(u * u2, u * u3);
    auto c1 = Vector2f(a22, a12) * testVec;
    auto c2 = Vector2f(a12, a11) * testVec;

    return c1 >= 0.f && c2 >= 0.f && c1 + c2 <= 1.f;
}
