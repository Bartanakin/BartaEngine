add_subdirectory(BartaShapes)

target_sources(${LIBRARY_NAME} PUBLIC
    Transformation.cpp
    Segment.cpp
    Ray.cpp
    Intersections.cpp
)