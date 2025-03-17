#pragma once
#include <Geometrics/Point.h>
#include <Graphics/Color.h>

namespace Barta::Graphics::OpenGL_Bridge {

struct Vertex {
    Point position;
    float red;
    float green;
    float blue;

    Vertex(
        Point position,
        Color color
    ) noexcept:
        position(position),
        red(Vertex::convertColorFormat(color.r)),
        green(Vertex::convertColorFormat(color.g)),
        blue(Vertex::convertColorFormat(color.b)) {}

    Vertex(
        Point position,
        float red,
        float green,
        float blue
    ) noexcept:
        position(position),
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
    return {M * v.position, v.red, v.green, v.blue};
}
}
