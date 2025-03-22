#pragma once
#include <Geometrics/Transformation.h>
#include <Graphics/OpenGL_Bridge/AbstractBufferGuard.h>
#include <Graphics/OpenGL_Bridge/UniformBuffer.h>
#include <pch.h>

namespace Barta::Graphics::OpenGL_Bridge {
class PV_BufferGuard: public AbstractBufferGuard {
    const UniformBuffer& uniformBuffer;

public:
    PV_BufferGuard(const UniformBuffer& uniformBuffer);

    void bufferData(const Transformation& transformation) const;

    ~PV_BufferGuard();
};
}
