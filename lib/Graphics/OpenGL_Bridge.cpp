#include <Graphics/OpenGL_Bridge.h>
#include "Graphics/OpenGL_Bridge/AttributeArrayGuard.h"
#include "Graphics/OpenGL_Bridge/IndexArrayGuard.h"
#include "Graphics/OpenGL_Bridge/PV_BufferGuard.h"
#include "Graphics/OpenGL_Bridge/VertexArrayGuard.h"
#include <Graphics/OpenGL_Bridge/Shader.h>

namespace Barta::Graphics::OpenGL_Bridge {

void framebuffer_size_callback(
    GLFWwindow* window,
    int width,
    int height
) {
    glViewport(0, 0, width, height);
}

OpenGL_Bridge::OpenGL_Bridge() noexcept:
    window(nullptr),
    vertexArray(nullptr),
    attributeArray(nullptr),
    view(Transformation::Identity()),
    projection(Transformation::Identity()) {}

void OpenGL_Bridge::createWindow(
    Vector2f size,
    std::string title
) {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (this->window != nullptr) {
        throw std::runtime_error("OpenGL window is already initialized");
    }

    this->window = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(this->window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    this->shader = std::make_unique<Shader>(
        std::string(BARTA_ENGINE_DIR) + "/shaders/vertex_shader.glsl",
        std::string(BARTA_ENGINE_DIR) + "/shaders/fragment_shader.glsl"
    );

    glClearColor(0.81f, 0.81f, 0.8f, 1.0f);

    glUseProgram(this->shader->getID());

    this->vertexArray = std::make_unique<VertexArray>();
    this->attributeArray = std::make_unique<AttributeArray>();
    this->PB_uniformBuffer = std::make_unique<UniformBuffer>(UniformBinding::VIEW_PROJECTION_MATRIX);

    this->projection = Transformation::perspective(0.1f, 2000.f, size.y / size.x, std::tan(M_PI / 4.f)) * Transformation::Identity();

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glEnable(GL_DEPTH_TEST);
}

void OpenGL_Bridge::drawObjects(
    std::list<GraphicsDataAwareInterface*>& objects
) {
    auto xd = 0;
    for (const auto& object: objects) {
        for (auto graphicsData_ptr: object->getGraphicsData()) {
            if (graphicsData_ptr->resource.getResourceId() != 0) {
                continue;
            }

            auto data = graphicsData_ptr->resource.getData().data();
            const auto& transformation = graphicsData_ptr->transformation;
            std::vector<Vertex> vertices;
            for (auto type: graphicsData_ptr->resource.getSpriteType()) {
                if (type == SpriteType::CIRCLE) {
                    Point center(data[0], data[1], data[2]);
                    float radius = data[3];
                    Color color(data[4], data[5], data[6], data[7]);

                    auto segmentCount = static_cast<unsigned int>(2.f * M_PI * radius);
                    auto initialIndex = this->vertexArray->getNextVertexIndex();
                    Vertex centerVertex(center, color);
                    vertices.push_back(centerVertex);
                    for (unsigned int i = 0; i < segmentCount; i++) {
                        float angle = 2.f * static_cast<float>(i) * M_PI / segmentCount;
                        vertices.emplace_back(center + Vector(radius * cos(angle), radius * sin(angle), 0.f), color);

                        this->vertexArray->addTrianglePrimitive({
                            initialIndex,
                            static_cast<GLubyte>(initialIndex + 1u + i),
                            static_cast<GLubyte>(initialIndex + 1u + (i + 1u) % segmentCount),
                        });
                    }
                } else if (type == SpriteType::TRIANGLE) {
                    Point p1(data[0], data[1], data[2]);
                    Point p2(data[3], data[4], data[5]);
                    Point p3(data[6], data[7], data[8]);
                    Color c1(data[9], data[10], data[11], data[12]);
                    Color c2(data[13], data[14], data[15], data[16]);
                    Color c3(data[17], data[18], data[19], data[20]);
                    auto initialIndex = this->vertexArray->getNextVertexIndex();
                    vertices = {
                        {p1, c1},
                        {p2, c2},
                        {p3, c3}
                    };

                    this->vertexArray->addTrianglePrimitive(
                        {initialIndex, static_cast<GLubyte>(initialIndex + 1u), static_cast<GLubyte>(initialIndex + 2)}
                    );
                    xd++;
                } else if (type == SpriteType::RECTANGLE_WITH_COLORS) {
                    Point p1(data[0], data[1], data[2]);
                    Point p2(data[0] + data[3], data[1], data[2]);
                    Point p3(data[0] + data[3], data[1] + data[4], data[2]);
                    Point p4(data[0], data[1] + data[4], data[2]);
                    Color c1(data[6], data[7], data[8], data[9]);
                    Color c2(data[10], data[11], data[12], data[13]);
                    Color c3(data[14], data[15], data[16], data[17]);
                    Color c4(data[18], data[19], data[20], data[21]);
                    auto initialIndex = this->vertexArray->getNextVertexIndex();
                    vertices = {
                        {p1, c1},
                        {p2, c2},
                        {p3, c3},
                        {p4, c4}
                    };

                    this->vertexArray->addTrianglePrimitive(
                        {initialIndex, static_cast<GLubyte>(initialIndex + 1u), static_cast<GLubyte>(initialIndex + 2)}
                    );
                    this->vertexArray->addTrianglePrimitive(
                        {initialIndex, static_cast<GLubyte>(initialIndex + 2u), static_cast<GLubyte>(initialIndex + 3)}
                    );
                }

                for (auto& vertex: vertices) {
                    vertex = transformation.getMatrix() * vertex;
                }

                this->vertexArray->addVertices(vertices);
                data += BartaSprite::getSpriteTypeSize(type);
            }
        }
    }

    {
        VertexArrayGuard vertexArrayGuard(*this->vertexArray);
        vertexArrayGuard.bufferVertices();
    }

    {
        AttributeArrayGuard attributeArrayGuard(*this->attributeArray);
        VertexArrayGuard vertexArrayGuard(*this->vertexArray);
        attributeArrayGuard.defineAttributePointer();
    }

    {
        AttributeArrayGuard attributeArrayGuard(*this->attributeArray);
        IndexArrayGuard indexArrayGuard(*this->vertexArray);
        AttributeArrayGuard innerAttributeArrayGuard(std::move(attributeArrayGuard));
        indexArrayGuard.bufferIndices();
    }

    {
        PV_BufferGuard PV_bufferGuard(*this->PB_uniformBuffer);
        Matrix PV = this->projection.getMatrix() * this->view.getMatrix();
        PV_bufferGuard.bufferData(PV);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    {
        AttributeArrayGuard attributeArrayGuard(*this->attributeArray);
        glDrawElements(GL_TRIANGLES, 3 * this->vertexArray->getNextVertexIndex(), GL_UNSIGNED_BYTE, reinterpret_cast<GLvoid*>(0));
    }

    glfwSwapBuffers(this->window);

    this->vertexArray->clear();
}

bool OpenGL_Bridge::logEvents(
    BartaEventLoggerInterface& eventLogger
) {
    if (glfwWindowShouldClose(this->window)) {
        return false;
    }

    glfwPollEvents();
    if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(this->window, true);
    }

    return true;
}

Transformation& OpenGL_Bridge::getViewTransformation() noexcept {
    return this->view;
}

OpenGL_Bridge::~OpenGL_Bridge() noexcept {
    glfwTerminate();
}

} // Barta
