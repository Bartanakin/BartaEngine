add_subdirectory(BartaShapes)

target_sources(${LIBRARY_NAME} PUBLIC
    Segment.cpp
    Ray.cpp
    Intersections.cpp
)