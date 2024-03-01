add_subdirectory(BartaShapes)
add_subdirectory(Math)

target_sources(${LIBRARY_NAME} PUBLIC
    Segment.cpp
    SFML_Transformable.cpp
    Vector2f.cpp
)