#include <Geometrics/BartaShapes/Triangle.h>
#include "Geometrics/ConvexFactor.h"
#include <pch.h>

namespace Barta {
Triangle::Triangle(
    Point p1,
    Point p2,
    Point p3
) noexcept:
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

Vector Triangle::getNormal() const noexcept {
    return (this->p1 - this->p2).cross(this->p1 - this->p3);
}

Point Triangle::getCenter() const {
    return ConvexFactor::baricentricCombination(std::array{this->p1, this->p2, this->p3});
}

Point Triangle::operator[](
    unsigned int index
) const noexcept {
    return *(&this->p1 + index);
}

Point Triangle::closestPoint(
    Point C
) const noexcept {
    for (int i = 0; i < 3; ++i) {
        if (this->belongsToUij(C, i, (i + 1) % 3) && this->belongsToUij(C, i, (i + 2) % 3)) {
            return this->operator[](i);
        }
    }

    auto n = this->getNormal();
    for (int i = 0; i < 3; ++i) {
        if (!this->belongsToUij(C, (i + 1) % 3, i) && !this->belongsToUij(C, i, (i + 1) % 3)
            && n.dot((this->operator[](i) - C).cross(this->operator[]((i + 1) % 3) - C)) <= 0) {
            return C - (this->operator[]((i + 1) % 3) - this->operator[](i)).perp(C - this->operator[](i));
        }
    }

    return C - n.proj(C - this->operator[](0));
}

std::array<PrecisionType, 3> Triangle::getConvexCoordinates(
    Point X
) const noexcept {
    using Matrix2 = Eigen::Matrix<PrecisionType, 2, 2>;
    using Vector2 = Eigen::Vector<PrecisionType, 2>;
    Matrix2 A;
    A(0,0) = (this->p2 - this->p1).dot(this->p2.toVector());
    A(1,0) = (this->p2 - this->p1).dot(this->p3.toVector());

    A(0,1) = (this->p3 - this->p1).dot(this->p2.toVector());
    A(1,1) = (this->p3 - this->p1).dot(this->p3.toVector());

    Vector2 b;
    b[0] = (X - this->p1).dot(this->p2.toVector());
    b[1] = (X - this->p1).dot(this->p3.toVector());

    auto alpha = A.inverse() * b;

    return {1. - alpha[0] - alpha[1], alpha[0], alpha[1]};
}

bool Triangle::belongsToUij(
    Point P,
    unsigned int i,
    unsigned int j
) const {
    return (this->operator[](j) - this->operator[](i)).dot(P - this->operator[](i)) < 0;
}
}
