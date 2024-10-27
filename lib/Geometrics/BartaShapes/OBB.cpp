//
// Created by bartanakin on 10/26/24.
//

#include <Geometrics/BartaShapes/OBB.h>

Barta::OBB::OBB(
    const Vector2f& leftTop,
    const Vector2f& widthHeight,
    float rotation
):
    AABB(leftTop, widthHeight),
    rotation(rotation) {}

Barta::Vector2f Barta::OBB::getFirstVertex() const noexcept {
    return AABB::getLeftTop();
}

std::vector<Barta::Segment> Barta::OBB::getSides() const noexcept {
    auto rotatedSides = decltype(AABB::getSides())();
    for (const auto& side : AABB::getSides()) {
        rotatedSides.emplace_back(side.getBeginning().rotated(this->rotation), side.getEnd().rotated(this->rotation));
    }

    return rotatedSides;
}

Barta::Vector2f Barta::OBB::rebasePoint(Vector2f p) const {
    return (p - this->getLeftTop()).rotated(-this->rotation);
}

Barta::Vector2f Barta::OBB::rebaseVector(Vector2f v) const {
    return v.rotated(-this->rotation);
}

std::vector<Barta::Vector2f> Barta::OBB::getVertices() const noexcept {
    return {
        this->getFirstVertex(),
        this->getSecondVertex(),
        this->getThirdVertex(),
        this->getFourthVertex()
    };
}

Barta::Vector2f Barta::OBB::getSecondVertex() const {
    return Vector2f{this->getWidthHeight().x, 0.f}.rotated(this->rotation) + this->getFirstVertex();
}

Barta::Vector2f Barta::OBB::getThirdVertex() const {
    return this->getWidthHeight().rotated(this->rotation) + this->getFirstVertex();
}

Barta::Vector2f Barta::OBB::getFourthVertex() const {
    return Vector2f{0.f, this->getWidthHeight().y}.rotated(this->rotation) + this->getFirstVertex();
}
