#include <Graphics/OpenGL_Bridge/PV_BufferGuard.h>

namespace Barta::Graphics::OpenGL_Bridge {
PV_BufferGuard::PV_BufferGuard(
    const UniformBuffer& uniformBuffer
):
    uniformBuffer(uniformBuffer) {
    if (AbstractBufferGuard::boundBufferHandle) {
        throw std::runtime_error("Buffer already locked");
    }

    AbstractBufferGuard::boundBufferHandle = this->uniformBuffer.getUniformBufferHandle();

    glBindBuffer(GL_UNIFORM_BUFFER, this->uniformBuffer.getUniformBufferHandle());
    auto error = glGetError();
    if (error != GL_NO_ERROR) {
        throw std::runtime_error("Uniform buffer not bound: " + error);
    }
}

void PV_BufferGuard::bufferData(
    const Matrix& transformation
) const {
    constexpr unsigned int BUFFER_SIZE = 16 * sizeof(PrecisionType);

    glBufferData(GL_UNIFORM_BUFFER, BUFFER_SIZE, nullptr, GL_STATIC_DRAW);
    auto error = glGetError();
    if (error != GL_NO_ERROR) {
        throw std::runtime_error("Uniform buffer allocation error: " + error);
    }

    glBufferSubData(GL_UNIFORM_BUFFER, 0, BUFFER_SIZE, &transformation);
    error = glGetError();
    if (error != GL_NO_ERROR) {
        throw std::runtime_error("Uniform buffer data loading error: " + error);
    }
}

PV_BufferGuard::~PV_BufferGuard() {
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    AbstractBufferGuard::boundBufferHandle = 0;
}
}
