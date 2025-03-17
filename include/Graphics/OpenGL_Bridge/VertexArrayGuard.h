#pragma once
#include "AbstractBufferGuard.h"
#include <Graphics/OpenGL_Bridge/VertexArray.h>
#include <pch.h>

namespace Barta::Graphics::OpenGL_Bridge {
class VertexArrayGuard: public AbstractBufferGuard {
    static GLuint g_currentIndexArrayHandle;
    const VertexArray& vertexArray;

public:
    VertexArrayGuard(const VertexArray&);

    void bufferVertices() const;

    ~VertexArrayGuard();
};
}
