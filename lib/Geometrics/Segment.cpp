#include <Geometrics/Segment.h>
#include <pch.h>

Barta::Segment::Relation Barta::Segment::calculateRelationToPoint(
    const Vector2f& point
) const noexcept {
    auto result =
        (this->beg.getX() - point.getX()) * (this->end.getY() - point.getY()) - (this->beg.getY() - point.getY()) * (this->end.getX() - point.getX());
    if (result > 0.f) {
        return Relation::RIGHT;
    }

    if (result < 0.f) {
        return Relation::LEFT;
    }

    return Relation::COLINEAR;
}

float Barta::Segment::calculateSquareDistanceFrom(
    const Vector2f& point
) const noexcept {
    return (this->getEnd() - this->getBeginning()).perp(point - this->getBeginning()).normSquare();
}
