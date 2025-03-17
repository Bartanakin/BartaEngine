#include <Graphics/OpenGL_Bridge/AttributeArray.h>

namespace Barta::Graphics::OpenGL_Bridge {
AttributeArray::AttributeArray() {
    glGenVertexArrays(1, &this->attributeArrayHandle);
    auto error = glGetError();
    if (error != GL_NO_ERROR) {
        throw new std::runtime_error("Attribute array not generated: " + error);
    }
}
}
