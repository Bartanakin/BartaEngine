#include <Graphics/OpenGL_Bridge/VertexArray.h>

namespace Barta::Graphics::OpenGL_Bridge {

VertexArray::VertexArray() {
    glGenBuffers(1, &this->vertexBufferHandle);
    auto error = glGetError();
    if (error != GL_NO_ERROR) {
        throw std::runtime_error("OpenGL Error: " + error);
    }

    glGenBuffers(1, &this->indexBufferHandle);
    error = glGetError();
    if (error != GL_NO_ERROR) {
        throw std::runtime_error("OpenGL Error: " + error);
    }
}

void VertexArray::addVertices(
    const std::vector<Vertex>& vertices
) noexcept {
    if (vertices.empty()) {
        return;
    }

    this->vertices.insert(this->vertices.end(), vertices.begin(), vertices.end());
}

void VertexArray::addTrianglePrimitives(
    std::vector<TrianglePrimitive> triangles
) noexcept {
    this->triangles.insert(this->triangles.end(), triangles.begin(), triangles.end());
}

void VertexArray::clear() {
    this->vertices.clear();
    this->triangles.clear();
}

void VertexArray::addTrianglePrimitive(
    unsigned int i1,
    unsigned int i2,
    unsigned int i3
) noexcept {
    this->triangles.push_back({
        static_cast<GLuint>(i1),
        static_cast<GLuint>(i2),
        static_cast<GLuint>(i3),
    });
}

}
