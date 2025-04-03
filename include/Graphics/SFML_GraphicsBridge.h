#pragma once

#include <Graphics/BartaGraphicsBridgeInterface.h>
#include <Graphics/GraphicsDataAwareInterface.h>
#include <Graphics/SFML_Bridge/NullResourceContainer.h>
#include <Graphics/SFML_Bridge/ResourceContainerInterface.h>
#include <Graphics/SFML_Bridge/ResourceMatcherInterface.h>

namespace Barta {
class SFML_GraphicsBridge: public BartaGraphicsBridgeInterface {
public:
    SFML_GraphicsBridge(
        std::unique_ptr<ResourceContainerInterface> resourceContainer = std::make_unique<NullResourceContainer>(),
        const std::filesystem::path& filePath = ""
    ) noexcept;
    SFML_GraphicsBridge(const std::filesystem::path& filePath) noexcept;
    SFML_GraphicsBridge(const SFML_GraphicsBridge&) noexcept = delete;
    SFML_GraphicsBridge(SFML_GraphicsBridge&&) noexcept = delete;
    SFML_GraphicsBridge& operator=(const SFML_GraphicsBridge&) noexcept = delete;
    ~SFML_GraphicsBridge() override;

    void createWindow(Vector2f size, std::string title) override;

    void drawObjects(std::list<GraphicsDataAwareInterface*>& objects) override;

    bool logEvents(BartaEventLoggerInterface& eventLogger) override;

    static const sf::Transform convertTransformation(const Transformation& myTransformation);

    Transformation& getViewTransformation() noexcept override { throw std::runtime_error("Not implemented"); }

private:
    void handleCustomResource(GraphicsData& graphicsData);

    sf::RenderWindow* sf_window;
    std::unique_ptr<RecourseMatcherInterface> resourceMatcher;
    std::unique_ptr<sf::Font> font;
};
}
