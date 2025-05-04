#include <Graphics/OpenGL_Bridge/AttributeArrayGuard.h>
#include <Graphics/OpenGL_Bridge/Vertex.h>

namespace Barta::Graphics::OpenGL_Bridge {
GLuint AttributeArrayGuard::boundAttributeArray = 0;

AttributeArrayGuard::AttributeArrayGuard(
    const AttributeArray& attributeArray
):
    attributeArray(attributeArray) {
    if (AttributeArrayGuard::boundAttributeArray) {
        throw std::runtime_error("AttributeArray already bound");
    }

    AttributeArrayGuard::boundAttributeArray = attributeArray.getAttributeArrayHandle();
    glBindVertexArray(this->attributeArray.getAttributeArrayHandle());
    auto error = glGetError();
    if (error != GL_NO_ERROR) {
        throw std::runtime_error("AttributeArray buffer not bound: " + error);
    }
}

AttributeArrayGuard::AttributeArrayGuard(
    AttributeArrayGuard&& other
):
    attributeArray(other.attributeArray) {
    other.moved = true;
}

void AttributeArrayGuard::defineAttributePointer() const {
    constexpr auto STRIDE = sizeof(Vertex);
    auto offset = 0;
    glEnableVertexAttribArray(static_cast<GLuint>(AttributeArray::AttributeEnum::POSITION));
    glVertexAttribPointer(
        static_cast<GLuint>(AttributeArray::AttributeEnum::POSITION),
        4,
        GL_FLOAT,
        GL_FALSE,
        STRIDE,
        reinterpret_cast<GLvoid*>(offset)
    );

    offset += 4 * sizeof(float);
    glEnableVertexAttribArray(static_cast<GLuint>(AttributeArray::AttributeEnum::COLOR));
    glVertexAttribPointer(
        static_cast<GLuint>(AttributeArray::AttributeEnum::COLOR),
        3,
        GL_FLOAT,
        GL_FALSE,
        STRIDE,
        reinterpret_cast<GLvoid*>(offset)
    );
}

AttributeArrayGuard::~AttributeArrayGuard() {
    if (this->moved) {
        return;
    }

    AttributeArrayGuard::boundAttributeArray = 0;
    glBindVertexArray(0);
}
}
