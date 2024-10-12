#pragma once
#include "../Vector2f.h"

namespace Barta {

class Triangle {
public:
    Triangle(Vector2f p1, Vector2f p2, Vector2f p3);

    bool isWithin(Vector2f point) const noexcept;

    const Vector2f p1;
    const Vector2f p2;
    const Vector2f p3;
};

inline std::ostream& operator<<(
    std::ostream& stream,
    const Triangle& triangle
) noexcept {
    return stream << "(" << triangle.p1 << ", " << triangle.p2 << ", " << triangle.p2 << ")";
}
}
