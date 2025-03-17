#pragma once
#include <Graphics/BartaGraphicsBridgeInterface.h>
#include <Graphics/OpenGL_Bridge/AttributeArray.h>
#include <Graphics/OpenGL_Bridge/Shader.h>
#include <Graphics/OpenGL_Bridge/ShaderUseGuard.h>
#include <Graphics/OpenGL_Bridge/VertexArray.h>
#include <pch.h>

namespace Barta::Graphics::OpenGL_Bridge {

class OpenGL_Bridge: public BartaGraphicsBridgeInterface {
public:
    OpenGL_Bridge() noexcept;
    void createWindow(Vector2f size, std::string title) override;

    void drawObjects(std::list<GraphicsDataAwareInterface*>& objects) override;

    bool logEvents(BartaEventLoggerInterface& eventLogger) override;

    ~OpenGL_Bridge() noexcept;

private:
    GLFWwindow* window;
    std::unique_ptr<Shader> shader;
    ShaderUseGuard shaderUseGuard;
    std::unique_ptr<VertexArray> vertexArray;
    std::unique_ptr<AttributeArray> attributeArray;
    Transformation camera2D;
};

} // Barta
