#pragma once
#include "../Segment.h"

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

    AABB(const Vector2f& leftTop, const Vector2f& widthHeight);

    /*
        The vector to the left top corner of the rectangle
    */
    Vector2f getLeftTop() const;

    /*
        The vector to the left top corner of the rectangle
    */
    Vector2f getRightTop() const;

    /*
        The vector to the left top corner of the rectangle
    */
    Vector2f getRightBottom() const;

    /*
        The vector to the left top corner of the rectangle
    */
    Vector2f getLeftBottom() const;

    /*
        The size of the rectangle
    */
    Vector2f getWidthHeight() const;

    /*
        All sides as Segments in clockwise orientation starting from the top
    */
    std::vector<Segment> getSides() const noexcept;

    /*
        All sides as Segments in clockwise orientation starting from the top
    */
    std::vector<Vector2f> getVertices() const noexcept;

    /*
        Wheater the point is inside the AABB
    */
    bool isWithin(const Vector2f&) const noexcept;

    VoronoiRegion findVoronoiRegionType(const Vector2f& point) const noexcept;

private:
    const Vector2f leftTop;
    const Vector2f widthHeight;
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
    return stream << "(" << aabb.getLeftTop() << ", " << aabb.getWidthHeight() << ")";
}
}
