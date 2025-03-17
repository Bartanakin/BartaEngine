#pragma once
#include <Graphics/OpenGL_Bridge/AttributeArray.h>
#include <pch.h>

namespace Barta::Graphics::OpenGL_Bridge {
class AttributeArrayGuard {
    static GLuint boundAttributeArray;
    const AttributeArray& attributeArray;
    bool moved = false;

public:
    AttributeArrayGuard(const AttributeArray&);
    AttributeArrayGuard(AttributeArrayGuard&&);

    void defineAttributePointer() const;

    ~AttributeArrayGuard();
};
}
