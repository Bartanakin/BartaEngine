#include <Graphics/SFML_GraphicsBridge.h>
#include <Geometrics/SFML_Transformable.h>
#include <Graphics/SFML_Bridge/SpriteResourceMatcher.h>

Barta::SFML_GraphicsBridge::SFML_GraphicsBridge(
    std::unique_ptr<ResourceContainerInterface> resourceContainer,
    const std::string& repositoryDir
) noexcept:
    sf_window(nullptr),
    resourceMatcher(std::make_unique<SpriteResourceMatcher>(std::move(resourceContainer))),
    arialFont(std::make_unique<sf::Font>()) {
    if (!repositoryDir.empty()) {
        arialFont->loadFromFile(repositoryDir + "\\fonts\\arial.ttf");
    }
}

Barta::SFML_GraphicsBridge::~SFML_GraphicsBridge() {
    delete this->sf_window;
}

void Barta::SFML_GraphicsBridge::createWindow(
    Vector2f size,
    std::string title
) {
    delete this->sf_window;
    this->sf_window = new sf::RenderWindow(sf::VideoMode(static_cast<unsigned int>(size.getX()), static_cast<unsigned int>(size.getY())), title);
    this->sf_window->setFramerateLimit(59);
}

void Barta::SFML_GraphicsBridge::drawObjects(
    std::list<GraphicsDataAwareInterface*>& objects
) {
    this->sf_window->clear();

    for (const auto& object: objects) {
        for (auto graphicsData_ptr: object->getGraphicsData()) {
            if (graphicsData_ptr->resource.getResourceId() == 0) {
                this->handleCustomResource(*graphicsData_ptr);

                continue;
            }

            auto hash = static_cast<const void*>(object);
            if (object->isToBeDeleted()) {
                this->resourceMatcher->drop(hash);

                continue;
            }

            this->resourceMatcher->matchResource(hash, graphicsData_ptr->resource.getResourceId());
            this->sf_window->draw(
                this->resourceMatcher->matchAndTransform(hash, SFML_GraphicsBridge::convertTransformable(*graphicsData_ptr->transformable))
            );
        }
    }

    this->sf_window->display();
}

bool Barta::SFML_GraphicsBridge::logEvents(
    BartaEventLoggerInterface& eventLogger
) {
    sf::Event event = sf::Event();
    while (this->sf_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            this->sf_window->close();

            return false;
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left) {
            eventLogger.logEvent(LeftClickEvent(Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y))));
        }

        if (event.type == sf::Event::MouseMoved) {
            eventLogger.logEvent(MouseMoveEvent(Vector2f(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y))));
        }

        BartaKeyMap key = static_cast<BartaKeyMap>(event.key.code);

        if (event.type == sf::Event::KeyPressed) {
            eventLogger.logEvent(KeyPressedEvent(key));
        }

        if (event.type == sf::Event::KeyReleased) {
            eventLogger.logEvent(KeyReleasedEvent(key));
        }
    }

    return true;
}

const sf::Transformable Barta::SFML_GraphicsBridge::convertTransformable(
    const TransformableInterface& myTransformable
) {
    auto newTransformable = sf::Transformable();
    auto myVector = myTransformable.getPosition();
    newTransformable.setPosition(myVector.getX(), myVector.getY());
    newTransformable.setRotation(myTransformable.getRotaion());

    return newTransformable;
}

void Barta::SFML_GraphicsBridge::handleCustomResource(
    GraphicsData& graphicsData
) {
    std::vector<float>::size_type dataOffset = 0;
    for (auto type: graphicsData.resource.getSpriteType()) {
        auto data = graphicsData.resource.getData();
        auto sf_transformable = SFML_GraphicsBridge::convertTransformable(*graphicsData.transformable);
        auto transform = sf_transformable.getTransform();

        if (type == SpriteType::RECTABGLE_WITH_COLORS) {
            auto rectangle = sf::VertexArray(sf::PrimitiveType::Triangles, 6);
            auto leftTopVertex = sf::Vertex(
                transform.transformPoint(data[dataOffset], data[dataOffset + 1]),
                sf::Color(
                    static_cast<sf::Uint8>(data[dataOffset + 6]),
                    static_cast<sf::Uint8>(data[dataOffset + 7]),
                    static_cast<sf::Uint8>(data[dataOffset + 8]),
                    static_cast<sf::Uint8>(data[dataOffset + 9])
                )
            );
            auto rightTopVertes = sf::Vertex(
                transform.transformPoint(data[dataOffset], data[dataOffset + 1] + data[dataOffset + 4]),
                sf::Color(
                    static_cast<sf::Uint8>(data[dataOffset + 10]),
                    static_cast<sf::Uint8>(data[dataOffset + 11]),
                    static_cast<sf::Uint8>(data[dataOffset + 12]),
                    static_cast<sf::Uint8>(data[dataOffset + 13])
                )
            );
            auto rightBottomVertes = sf::Vertex(
                transform.transformPoint(data[dataOffset] + data[dataOffset + 3], data[dataOffset + 1] + data[dataOffset + 4]),
                sf::Color(
                    static_cast<sf::Uint8>(data[dataOffset + 14]),
                    static_cast<sf::Uint8>(data[dataOffset + 15]),
                    static_cast<sf::Uint8>(data[dataOffset + 16]),
                    static_cast<sf::Uint8>(data[dataOffset + 17])
                )
            );
            auto leftBottomVertex = sf::Vertex(
                transform.transformPoint(data[dataOffset] + data[dataOffset + 3], data[dataOffset + 1]),
                sf::Color(
                    static_cast<sf::Uint8>(data[dataOffset + 18]),
                    static_cast<sf::Uint8>(data[dataOffset + 19]),
                    static_cast<sf::Uint8>(data[dataOffset + 20]),
                    static_cast<sf::Uint8>(data[dataOffset + 21])
                )
            );

            rectangle[0] = leftTopVertex;
            rectangle[1] = leftBottomVertex;
            rectangle[2] = rightBottomVertes;
            rectangle[3] = rightBottomVertes;
            rectangle[4] = rightTopVertes;
            rectangle[5] = leftTopVertex;

            this->sf_window->draw(rectangle);

            dataOffset += 6 + 4 * 4;
        }

        if (type == SpriteType::CIRCLE) {
            auto circleShape = sf::CircleShape(data[dataOffset + 3]);
            circleShape.setPosition(
                sf_transformable.getPosition() + sf::Vector2f(data[dataOffset] - data[dataOffset + 3], data[dataOffset + 1] - data[dataOffset + 3])
            );
            circleShape.setRotation(sf_transformable.getRotation());
            circleShape.setScale(sf_transformable.getScale());
            circleShape.setFillColor(sf::Color(
                static_cast<sf::Uint8>(data[dataOffset + 4]),
                static_cast<sf::Uint8>(data[dataOffset + 5]),
                static_cast<sf::Uint8>(data[dataOffset + 6]),
                static_cast<sf::Uint8>(data[dataOffset + 7])
            ));

            this->sf_window->draw(circleShape);

            dataOffset += 8;
        }

        if (type == SpriteType::VARCHAR256) {
            char c_string[64];

            std::copy(data.begin() + dataOffset + 4, data.begin() + dataOffset + 4 + 64, c_string);

            auto string = sf::String(c_string);
            auto text = sf::Text();
            text.setString(string);
            text.setFont(*this->arialFont);
            text.setCharacterSize(static_cast<unsigned int>(data[dataOffset + 3]));
            text.setPosition(data[dataOffset] + sf_transformable.getPosition().x, data[dataOffset + 1] + sf_transformable.getPosition().y);
            this->sf_window->draw(text);

            dataOffset += 3 + 1 + 64;
        }
    }
}

std::unique_ptr<Barta::TransformableInterface> Barta::SFML_GraphicsBridge::createNewTransformableInstance() {
    return std::unique_ptr<TransformableInterface>(new SFML_Transformable());
}
