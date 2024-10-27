//
// Created by bartanakin on 10/26/24.
//

#pragma once

#include "AABB.h"

namespace Barta {
class OBB: protected AABB {
public:
    OBB(const Vector2f& leftTop, const Vector2f& widthHeight, float rotation);

    Vector2f getFirstVertex() const noexcept;

    std::vector<Segment> getSides() const noexcept;

    bool isWithin(const Vector2f&) const noexcept;

    float getRotation() const noexcept { return this->rotation; }

    AABB getAABB() const {return *this; }

    Vector2f rebasePoint(Vector2f) const;

    Vector2f getWidthHeight() const noexcept { return AABB::getWidthHeight(); }

    Vector2f getThirdVertex() const;

    std::vector<Vector2f> getVertices() const noexcept;

    Vector2f getSecondVertex() const;

    Vector2f getFourthVertex() const;

    Vector2f rebaseVector(Vector2f v) const;

private:
    // radians
    float rotation;
};

inline std::ostream& operator<<(
    std::ostream& stream,
    const OBB& obb
) noexcept {
    return stream << "(" << obb.getFirstVertex() << ", " << obb.getWidthHeight() << ", " << obb.getRotation() << ")";
}
}
