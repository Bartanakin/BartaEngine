#pragma once
#include "Point.h"

namespace Barta {

class Segment {
public:
    Segment(
        Point beg,
        Point end
    ):
        beg(beg),
        end(end) {}

    enum class Relation {
        LEFT = -1,
        COLINEAR = 0,
        RIGHT = 1
    };

    Point getBeginning() const noexcept { return this->beg; }

    Point getEnd() const noexcept { return this->end; }

    float squareOfDistance() const noexcept { return beg.squaredDistance(end); }

    Relation calculateRelationToPoint(const Point& point) const noexcept;

    float calculateSquareDistanceFrom(const Point& point) const noexcept;

private:
    const Point beg;
    const Point end;
};

inline std::ostream& operator<<(
    std::ostream& stream,
    const Segment& I
) noexcept {
    return stream << "(" << I.getBeginning().toVector() << ", " << I.getEnd().toVector() << ")";
}
}
