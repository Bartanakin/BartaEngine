#pragma once
#include <pch.h>

namespace Barta::Graphics::OpenGL_Bridge {
class AttributeArray {
    GLuint attributeArrayHandle;

public:
    enum class AttributeEnum {
        POSITION = 0,
        COLOR = 1,
    };
    AttributeArray();

    GLuint getAttributeArrayHandle() const { return this->attributeArrayHandle; }
};
}
