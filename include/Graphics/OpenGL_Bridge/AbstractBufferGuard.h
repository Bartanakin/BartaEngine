#pragma once
#include <pch.h>

namespace Barta::Graphics::OpenGL_Bridge {
class AbstractBufferGuard {
protected:
    static GLuint boundBufferHandle;
};
}
