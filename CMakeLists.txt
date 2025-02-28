cmake_minimum_required(VERSION 3.16)


# Library Name
set(PROJECT_NAME "BartaEngine")
set(LIBRARY_NAME "BartaEngine_lib")
set(RUN_TEST_NAME "BartaEngine_runTest")

project(
        ${PROJECT_NAME}
        VERSION 2.0.0
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(eigen
        GIT_REPOSITORY https://gitlab.com/libeigen/eigen
        GIT_TAG 3.4.0)
FetchContent_MakeAvailable(eigen)

add_subdirectory(lib)
target_link_libraries(
        ${LIBRARY_NAME}
        PUBLIC
        sfml-graphics
)
target_link_libraries(${LIBRARY_NAME} PUBLIC eigen)
target_compile_features(${LIBRARY_NAME} PRIVATE cxx_std_20)

#if(WIN32)
#    add_custom_command(
#            TARGET ${PROJECT_NAME}
#            COMMENT "Copy OpenAL DLL"
#            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
#            VERBATIM)
#endif()

install(
        TARGETS ${LIBRARY_NAME}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
)

enable_testing()
add_subdirectory(test/run )

install(
        TARGETS ${RUN_TEST_NAME}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)