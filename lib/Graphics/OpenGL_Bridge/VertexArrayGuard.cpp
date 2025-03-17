#include <Graphics/OpenGL_Bridge/VertexArrayGuard.h>
#include <Graphics/OpenGL_Bridge/AbstractBufferGuard.h>

namespace Barta::Graphics::OpenGL_Bridge {

VertexArrayGuard::VertexArrayGuard(
    const VertexArray& vertexArray
):
    vertexArray(vertexArray) {
    if (AbstractBufferGuard::boundBufferHandle) {
        throw std::runtime_error("Buffer already locked");
    }

    AbstractBufferGuard::boundBufferHandle = vertexArray.getVertexBufferHandle();

    glBindBuffer(GL_ARRAY_BUFFER, vertexArray.getVertexBufferHandle());
    auto error = glGetError();
    if (error != GL_NO_ERROR) {
        throw std::runtime_error("Vertex buffer not bound: " + error);
    }
}

void VertexArrayGuard::bufferVertices() const {
    glBufferData(GL_ARRAY_BUFFER, this->vertexArray.getVertices().size() * sizeof(Vertex), this->vertexArray.getVertices().data(), GL_STATIC_DRAW);
    auto error = glGetError();
    if (error != GL_NO_ERROR) {
        throw std::runtime_error("Vertex buffer data loading error: " + error);
    }
}

VertexArrayGuard::~VertexArrayGuard() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    AbstractBufferGuard::boundBufferHandle = 0;
}
}
