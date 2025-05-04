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
    constexpr unsigned int BUFFER_SIZE = 16 * sizeof(float);

    glBufferData(GL_UNIFORM_BUFFER, BUFFER_SIZE, nullptr, GL_STATIC_DRAW);
    auto error = glGetError();
    if (error != GL_NO_ERROR) {
        throw std::runtime_error("Uniform buffer allocation error: " + error);
    }

    std::vector<float> data(16);
    for (unsigned int i = 0; i < 16; ++i) {
        data[i] = transformation(i % 4, i / 4);
    }

    glBufferSubData(GL_UNIFORM_BUFFER, 0, BUFFER_SIZE, data.data());
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
