#include <Graphics/OpenGL_Bridge/UniformBuffer.h>

namespace Barta::Graphics::OpenGL_Bridge {
UniformBuffer::UniformBuffer(
    UniformBinding uniformBinding
) {
    glGenBuffers(1, &this->uniformBufferHandle);
    glBindBufferBase(GL_UNIFORM_BUFFER, static_cast<unsigned int>(uniformBinding), this->uniformBufferHandle);
}
}
