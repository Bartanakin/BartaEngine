#pragma once
#include <Graphics/OpenGL_Bridge/UniformBinding.h>
#include <pch.h>

namespace Barta::Graphics::OpenGL_Bridge {
class UniformBuffer {
    GLuint uniformBufferHandle;

public:
    UniformBuffer(UniformBinding uniformBinding);

    GLuint getUniformBufferHandle() const { return uniformBufferHandle; }
};
}
