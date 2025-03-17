#include <Graphics/OpenGL_Bridge/IndexArrayGuard.h>

namespace Barta::Graphics::OpenGL_Bridge {

IndexArrayGuard::IndexArrayGuard(
    const VertexArray& vertexArray
):
    vertexArray(vertexArray) {
    if (AbstractBufferGuard::boundBufferHandle) {
        throw std::runtime_error("Buffer already locked");
    }

    AbstractBufferGuard::boundBufferHandle = vertexArray.getIndexBufferHandle();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArray.getIndexBufferHandle());
    auto error = glGetError();
    if (error != GL_NO_ERROR) {
        throw new std::runtime_error("Index buffer not bound: " + error);
    }
}

void IndexArrayGuard::bufferIndices() const {
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        this->vertexArray.getTriangles().size() * sizeof(TrianglePrimitive),
        this->vertexArray.getTriangles().data(),
        GL_STATIC_DRAW
    );
    auto error = glGetError();
    if (error != GL_NO_ERROR) {
        throw new std::runtime_error("Vertex buffer data loading error: " + error);
    }
}

IndexArrayGuard::~IndexArrayGuard() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    AbstractBufferGuard::boundBufferHandle = 0;
}
}
