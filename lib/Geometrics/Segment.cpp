#include <pch.h>
#include <Geometrics/Segment.h>

Barta::Segment::Relation Barta::Segment::calculateRelationToPoint(const Vector2f& point) const noexcept {
    auto result = (this->beg.getX() - point.getX()) * (this->end.getY() - point.getY()) - (this->beg.getY() - point.getY()) * (this->end.getX() - point.getX());
    if (result > 0.f) {
        return Relation::RIGHT;
    }

    if (result < 0.f) {
        return Relation::LEFT;
    }

    return Relation::COLINEAR;
}
