#pragma once
#include <Graphics/OpenGL_Bridge/AbstractBufferGuard.h>
#include <Graphics/OpenGL_Bridge/VertexArray.h>
#include <pch.h>

namespace Barta::Graphics::OpenGL_Bridge {
class IndexArrayGuard: public AbstractBufferGuard {
    const VertexArray& vertexArray;

public:
    IndexArrayGuard(const VertexArray&);

    void bufferIndices() const;

    ~IndexArrayGuard();
};
}
