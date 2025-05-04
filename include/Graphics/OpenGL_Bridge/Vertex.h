#pragma once
#include <Geometrics/Point.h>
#include <Graphics/Color.h>

namespace Barta::Graphics::OpenGL_Bridge {

struct Vertex {
    float x, y, z;
    float w = 1.f;
    float red;
    float green;
    float blue;

    Vertex(
        Point position,
        Color color
    ) noexcept:
        x(position.x()),
        y(position.y()),
        z(position.z()),
        red(Vertex::convertColorFormat(color.r)),
        green(Vertex::convertColorFormat(color.g)),
        blue(Vertex::convertColorFormat(color.b)) {}

    Vertex(
        Point position,
        float red,
        float green,
        float blue
    ) noexcept:
        x(position.x()),
        y(position.y()),
        z(position.z()),
        red(red),
        green(green),
        blue(blue) {}

    static float convertColorFormat(
        unsigned char v
    ) {
        return static_cast<float>(v) / 255.f;
    }
};

inline Vertex operator*(
    const Matrix& M,
    const Vertex& v
) noexcept {
    Point p = {v.x, v.y, v.z};

    return {M * p, v.red, v.green, v.blue};
}
}
