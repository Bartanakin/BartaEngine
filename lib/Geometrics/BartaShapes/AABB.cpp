#include <Geometrics/BartaShapes/AABB.h>
#include "pch.h"

namespace Barta {
AABB::AABB(
    const Point& leftTop,
    const Vector& widthHeight
):
    leftTop(leftTop),
    widthHeight(widthHeight) {}

Point AABB::getLeftTop() const {
    return this->leftTop;
}

Point AABB::getRightTop() const {
    return this->getLeftTop() + Vector(this->getWidthHeight().x(), 0.f);
}

Point AABB::getRightBottom() const {
    return this->getLeftTop() + this->getWidthHeight();
}

Point AABB::getLeftBottom() const {
    return this->getLeftTop() + Vector(0.f, this->getWidthHeight().y());
}

Vector AABB::getWidthHeight() const {
    return this->widthHeight;
}

std::vector<Segment> AABB::getSides() const noexcept {
    return {
        Segment(this->getLeftTop(), this->getRightTop()),
        Segment(this->getRightTop(), this->getRightBottom()),
        Segment(this->getRightBottom(), this->getLeftBottom()),
        Segment(this->getLeftBottom(), this->getLeftTop())
    };
}

std::vector<Point> AABB::getVertices() const noexcept {
    return {
        this->getLeftTop(),
        this->getRightTop(),
        this->getRightBottom(),
        this->getLeftBottom(),
    };
}

bool AABB::isWithin(
    const Point& point
) const noexcept {
    return this->leftTop.x() <= point.x() && point.x() <= this->leftTop.x() + this->widthHeight.x() && this->leftTop.y() <= point.y()
           && point.y() <= this->leftTop.y() + this->widthHeight.y();
}

AABB::PointDistance AABB::closestPointTo(
    Point p
) const noexcept {
    PointDistance q;
    q.distance = .0f;
    for (int i = 0; i < p.size(); i++) {
        auto coord = p[i];
        if (coord < this->getLeftTop()[i]) {
            coord = this->getLeftTop()[i];
            q.distance += std::pow(this->getLeftTop()[i] - coord, 2);
        }

        if (coord > this->getRightBottom()[i]) {
            coord = this->getRightBottom()[i];
            q.distance += std::pow(this->getRightBottom()[i] - coord, 2);
        }

        q.point[i] = coord;
    }

    return q;
}

AABB::VoronoiRegion AABB::findVoronoiRegionType(
    const Point& point
) const noexcept {
    auto sides = this->getSides();
    auto regionMask = VoronoiRegion::INSIDE;
    VoronoiRegion regionsMap[4] = {VoronoiRegion::TOP, VoronoiRegion::RIGHT, VoronoiRegion::BOTTOM, VoronoiRegion::LEFT};
    for (decltype(sides)::size_type i = 0; i < sides.size(); i++) {
        if (sides[i].calculateRelationToPoint(point) == Segment::Relation::LEFT) {
            regionMask = regionMask | regionsMap[i];
        }
    }

    return regionMask;
}
}
