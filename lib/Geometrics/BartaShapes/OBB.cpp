//
// Created by bartanakin on 10/26/24.
//

#include <Geometrics/BartaShapes/OBB.h>

namespace Barta {
OBB::OBB(
    const Point& position,
    const Vector& widthHeight,
    PrecisionType rotation
):
    widthHeight(widthHeight),
    transformation(Transformation::rotation(rotation, position) * Transformation::translation(position.toVector())) {}

OBB::OBB(
    const Vector& widthHeight,
    Transformation transformation
):
    widthHeight(widthHeight),
    transformation(std::move(transformation)) {}

Point OBB::getFirstVertex() const noexcept {
    return this->transformation.getTranslation() + Point::Zero();
}

std::vector<Segment> OBB::getSides() const noexcept {
    auto aabb = AABB(Point::Zero(), this->widthHeight);
    auto rotatedSides = decltype(aabb.getSides())();
    for (const auto& side: aabb.getSides()) {
        rotatedSides.emplace_back(this->transformation.getMatrix() * side.getBeginning(), this->transformation.getMatrix() * side.getEnd());
    }

    return rotatedSides;
}

AABB::PointDistance OBB::closestPointTo(
    Point p
) const noexcept {
    auto aabb = AABB(Point::Zero(), this->widthHeight);

    return aabb.closestPointTo(this->transformation.getMatrix().inverse() * p);
}

Point OBB::getCenter() const noexcept {
    return this->transformation.getMatrix() * (Point::Zero() + 0.5 * this->widthHeight);
}

const Transformation& OBB::getTransformation() const noexcept {
    return this->transformation;
}

std::vector<Point> OBB::getVertices() const noexcept {
    return {this->getFirstVertex(), this->getSecondVertex(), this->getThirdVertex(), this->getFourthVertex()};
}

Point OBB::getSecondVertex() const {
    return this->transformation.getMatrix() * (Point::Zero() + Vector(this->widthHeight.x(), 0.f));
}

Point OBB::getThirdVertex() const {
    return this->transformation.getMatrix() * (Point::Zero() + Vector(this->widthHeight));
}

Point OBB::getFourthVertex() const {
    return this->transformation.getMatrix() * (Point::Zero() + Vector(0.f, this->widthHeight.y()));
}
}
