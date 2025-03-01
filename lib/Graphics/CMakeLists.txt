add_subdirectory(SFML_Bridge)
add_subdirectory(SpriteBuilder)

target_sources(${LIBRARY_NAME} PUBLIC
    SFML_GraphicsBridge.cpp
    GraphicsDataTransformer.cpp
)