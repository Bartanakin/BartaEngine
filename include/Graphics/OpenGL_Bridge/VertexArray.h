#pragma once
#include <Graphics/OpenGL_Bridge/TrianglePrimitive.h>
#include <Graphics/OpenGL_Bridge/Vertex.h>
#include <pch.h>

namespace Barta::Graphics::OpenGL_Bridge {
class VertexArray {
    std::vector<Vertex> vertices;
    std::vector<TrianglePrimitive> triangles;
    GLuint vertexBufferHandle;
    GLuint indexBufferHandle;

public:
    VertexArray();

    VertexArray(const VertexArray& other) noexcept = delete;
    VertexArray& operator=(const VertexArray& other) noexcept = delete;

    void addVertices(const std::vector<Vertex>& vertices) noexcept;

    GLuint getNextVertexIndex() const noexcept { return this->vertices.size(); }

    GLuint getTriangleCount() const noexcept { return this->triangles.size(); }

    void addTrianglePrimitive(unsigned int i1, unsigned int i2, unsigned int i3) noexcept;

    void addTrianglePrimitives(std::vector<TrianglePrimitive> primitives) noexcept;

    GLuint getVertexBufferHandle() const { return this->vertexBufferHandle; }

    GLuint getIndexBufferHandle() const { return this->indexBufferHandle; }

    const std::vector<Vertex>& getVertices() const { return this->vertices; }

    const std::vector<TrianglePrimitive>& getTriangles() const { return this->triangles; }

    void clear();
};

}
