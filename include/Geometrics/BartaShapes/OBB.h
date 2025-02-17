//
// Created by bartanakin on 10/26/24.
//

#pragma once

#include <Geometrics/BartaShapes/AABB.h>

namespace Barta {
class OBB {
public:
    OBB(const Point& position, const Vector& widthHeight, PrecisionType rotation);
    // scale is always (1, 1, 1)
    OBB(const Vector& widthHeight, Transformation transformation);

    Point getFirstVertex() const noexcept;

    std::vector<Segment> getSides() const noexcept;

    bool isWithin(const Point&) const noexcept;

    PrecisionType getRotation(
        const Vector& axis = Vector::Z_Axis()
    ) const noexcept {
        return this->transformation.getRotation(axis);
    }

    Vector getWidthHeight() const noexcept { return this->widthHeight; }

    Point getThirdVertex() const;

    std::vector<Point> getVertices() const noexcept;

    Point getSecondVertex() const;

    Point getFourthVertex() const;

    AABB::PointDistance closestPointTo(Point) const noexcept;

    Point getCenter() const noexcept;

    const Transformation& getTransformation() const noexcept;

private:
    Vector widthHeight;
    Transformation transformation;
};

inline OBB operator*(
    const Matrix& M,
    const OBB& obb
) noexcept {
    // TODO scale
    auto T = Transformation(M);

    return {M * obb.getFirstVertex(), obb.getWidthHeight(), obb.getRotation() + T.getRotation(obb.getFirstVertex().toVector())};
}

inline std::ostream& operator<<(
    std::ostream& stream,
    const OBB& obb
) noexcept {
    return stream << "(" << obb.getFirstVertex().toVector() << ", " << obb.getWidthHeight() << ", " << obb.getRotation() << ")";
}
}
