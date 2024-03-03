add_library(${LIBRARY_NAME} STATIC
    Application.cpp
    BartaObjectManager.cpp
    pch.cpp
    DeleteWatchSingleton.cpp
    DeletableObject.cpp
)

# target_precompile_headers(${PROJECT_NAME} PUBLIC
#     "pch.h"
# )

add_subdirectory(Collisions)
add_subdirectory(Dynamics)
add_subdirectory(Events/Subscribers)
add_subdirectory(Geometrics)
add_subdirectory(Graphics)
add_subdirectory(Hitbox)
add_subdirectory(Objects)

target_include_directories(${LIBRARY_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/include")