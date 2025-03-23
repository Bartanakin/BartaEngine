cmake_minimum_required(VERSION 3.16)

# Library Name
set(LIBRARY_NAME "BartaEngine_lib")
set(BARTA_ENGINE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(RUN_TEST_NAME "BartaEngine_runTest")
set(USE_OPEN_GL 1)
set(USE_SFML 0)

project(
    ${LIBRARY_NAME}
    VERSION 2.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
if(USE_SFML)
    FetchContent_Declare(SFML
            GIT_REPOSITORY https://github.com/SFML/SFML.git
            GIT_TAG 2.6.x)
    FetchContent_MakeAvailable(SFML)
endif()

FetchContent_Declare(eigen
        GIT_REPOSITORY https://gitlab.com/libeigen/eigen
        GIT_TAG 3.4.0)
FetchContent_MakeAvailable(eigen)

FetchContent_Declare(json
        URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json)

add_subdirectory(lib)

if (USE_OPEN_GL)
    add_compile_definitions(USE_OPEN_GL=1)
    FetchContent_Declare(
            glfw
            GIT_REPOSITORY https://github.com/glfw/glfw.git
            GIT_TAG latest
    )
    FetchContent_MakeAvailable(glfw)
    FetchContent_Declare(
            glad
            GIT_REPOSITORY https://github.com/Dav1dde/glad.git
            GIT_TAG master
    )
    FetchContent_MakeAvailable(glad)

    link_libraries(OpenGL::GL glfw glm glad)
    target_link_libraries(${LIBRARY_NAME} PUBLIC glfw)
    target_link_libraries(${LIBRARY_NAME} PUBLIC glad)
#    target_link_libraries(${LIBRARY_NAME} PUBLIC OpenGL::GL)
endif ()


if (USE_SFML)
    target_link_libraries(
            ${LIBRARY_NAME}
            PUBLIC
            sfml-graphics
    )
endif()

target_link_libraries(${LIBRARY_NAME} PUBLIC eigen)
target_link_libraries(${LIBRARY_NAME} PUBLIC nlohmann_json::nlohmann_json)

target_compile_features(${LIBRARY_NAME} PRIVATE cxx_std_20)

target_compile_definitions(
        ${LIBRARY_NAME} PUBLIC BARTA_ENGINE_DIR="${BARTA_ENGINE_DIR}"
        ${LIBRARY_NAME} PUBLIC USE_OPEN_GL=${USE_OPEN_GL}
        ${LIBRARY_NAME} PUBLIC USE_SFML=${USE_SFML}
)


install(
        TARGETS ${LIBRARY_NAME}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
)

enable_testing()
#add_subdirectory(test/run )
#
#install(
#        TARGETS ${RUN_TEST_NAME}
#        ARCHIVE DESTINATION lib
#        LIBRARY DESTINATION lib
#        RUNTIME DESTINATION bin
#)