target_sources(${LIBRARY_NAME} PUBLIC
        GraphicsDataTransformer.cpp
)
add_subdirectory(SpriteBuilder)

if (USE_SFML)
    target_sources(${LIBRARY_NAME} PUBLIC
            SFML_GraphicsBridge.cpp
    )
    add_subdirectory(SFML_Bridge)
endif()

if(USE_OPEN_GL)
    target_sources(${LIBRARY_NAME} PUBLIC
            OpenGL_Bridge.cpp
    )
    add_subdirectory(OpenGL_Bridge)
endif ()

