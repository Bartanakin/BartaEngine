#pragma once
#include "BartaGraphicsBridgeInterface.h"
#include "SFML_Bridge/ResourceContainerInterface.h"
#include "SFML_Bridge/ResourceMatcherInterface.h"

namespace Barta{
    class SFML_GraphicsBridge :
        public BartaGraphicsBridgeInterface{
    public:
        SFML_GraphicsBridge(
            std::unique_ptr<Barta::ResourceContainerInterface> resourceContainer,
            const std::string repositoryDir
        ) noexcept;
        SFML_GraphicsBridge( const SFML_GraphicsBridge& ) noexcept = delete;
        SFML_GraphicsBridge(SFML_GraphicsBridge&&) noexcept = delete;
        SFML_GraphicsBridge& operator=(const SFML_GraphicsBridge&) noexcept = delete;
        virtual ~SFML_GraphicsBridge();

        void createWindow( Vector2f size, std::string title ) override;
        void drawObjects( const std::list<BartaObjectInterface*>& objects ) override;
        bool logEvents( BartaEventLoggerInterface& eventLogger ) override;

        static const sf::Transformable convertTransformable( const TransformableInterface& myTransformable );
    private:
        void handleCustomeResource(BartaObjectInterface& object);

        sf::RenderWindow* sf_window;
        std::unique_ptr<RecourseMatcherInterface>resourceMatcher;
        std::unique_ptr<sf::Font> arialFont;
    };
}

