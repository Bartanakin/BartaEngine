#pragma once
#include "../Segment.h"
#include <Geometrics/Transformation.h>

namespace Barta {

/*
    Axis Aligned Bounding Block
*/
class AABB {
public:
    enum class VoronoiRegion {
        INSIDE = 0,

        TOP = 1,
        RIGHT = 2,
        BOTTOM = 4,
        LEFT = 8,

        RIGTH_TOP = TOP + RIGHT,
        RIGTH_BOTTOM = BOTTOM + RIGHT,
        LEFT_BOTTOM = BOTTOM + LEFT,
        LEFT_TOP = TOP + LEFT
    };

    AABB() = default;
    AABB(const Point& leftTop, const Vector& widthHeight);

    /*
        The vector to the left top corner of the rectangle
    */
    Point getLeftTop() const;

    /*
        The vector to the left top corner of the rectangle
    */
    Point getRightTop() const;

    /*
        The vector to the left top corner of the rectangle
    */
    Point getRightBottom() const;

    /*
        The vector to the left top corner of the rectangle
    */
    Point getLeftBottom() const;

    /*
        The size of the rectangle
    */
    Vector getWidthHeight() const;

    /*
        All sides as Segments in clockwise orientation starting from the top
    */
    std::vector<Segment> getSides() const noexcept;

    /*
        All sides as Segments in clockwise orientation starting from the top
    */
    std::vector<Point> getVertices() const noexcept;

    /*
        Wheater the point is inside the AABB
    */
    bool isWithin(const Point&) const noexcept;

    struct PointDistance {
        float distance;
        Point point;
    };

    PointDistance closestPointTo(Point) const noexcept;

    VoronoiRegion findVoronoiRegionType(const Point& point) const noexcept;

private:
    Point leftTop;
    Vector widthHeight;
};

inline AABB::VoronoiRegion operator|(
    const AABB::VoronoiRegion& first,
    const AABB::VoronoiRegion& second
) noexcept {
    return static_cast<AABB::VoronoiRegion>(static_cast<int>(first) | static_cast<int>(second));
}

inline AABB::VoronoiRegion operator&(
    const AABB::VoronoiRegion& first,
    const AABB::VoronoiRegion& second
) noexcept {
    return static_cast<AABB::VoronoiRegion>(static_cast<int>(first) & static_cast<int>(second));
}

inline AABB::VoronoiRegion operator~(
    const AABB::VoronoiRegion& first
) noexcept {
    return static_cast<AABB::VoronoiRegion>(~static_cast<int>(first));
}

inline std::ostream& operator<<(
    std::ostream& stream,
    const AABB& aabb
) noexcept {
    return stream << "(" << aabb.getLeftTop().toVector() << ", " << aabb.getWidthHeight() << ")";
}

inline AABB operator*(
    const Matrix& M,
    const AABB& aabb
) noexcept {
    return {M * aabb.getLeftTop(), aabb.getWidthHeight()};
}
}
