#include <Geometrics/Segment.h>

// TODO third dimention
Barta::Segment::Relation Barta::Segment::calculateRelationToPoint(
    const Point& point
) const noexcept {
    auto result = (this->beg.x() - point.x()) * (this->end.y() - point.y()) - (this->beg.y() - point.y()) * (this->end.x() - point.x());
    if (result > 0.f) {
        return Relation::RIGHT;
    }

    if (result < 0.f) {
        return Relation::LEFT;
    }

    return Relation::COLINEAR;
}

float Barta::Segment::calculateSquareDistanceFrom(
    const Point& point
) const noexcept {
    return (this->getEnd() - this->getBeginning()).perp(point - this->getBeginning()).squaredNorm();
}
