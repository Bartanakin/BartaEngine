add_library(
    ${LIBRARY_NAME} BartaObjectManager.cpp pch.cpp
)

# target_precompile_headers(${PROJECT_NAME} PUBLIC
#     "pch.h"
# )

add_subdirectory(Collisions)
add_subdirectory(Dynamics)
add_subdirectory(Events)
add_subdirectory(Geometrics)
add_subdirectory(Graphics)
add_subdirectory(Hitbox)
add_subdirectory(Objects)
add_subdirectory(SceneLoader)
add_subdirectory(Utilities)

target_include_directories(${LIBRARY_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/include")

#if(${ENABLE_WARNINGS})
#    target_set_warnings(
#        TARGET
#        ${PROJECT_NAME}
#        ENABLE
#        ${ENABLE_WARNINGS}
#        AS_ERRORS
#        ${ENABLE_WARNINGS_AS_ERRORS})
#endif()

# if(${ENABLE_LTO})
#     target_enable_lto(
#         TARGE
#         ${PROJECT_NAME}
#         ENABLE
#         ON)
# endif()

#if(${ENABLE_CLANG_TIDY})
#    set(CMAKE_CXX_COMPILE_OPTIONS_USE_PCH -Winvalid-pch -x c++-header -include <PCH_HEADER>)
#    add_clang_tidy_to_target(${PROJECT_NAME})
#else()
#    message(STATUS "Not activating clang-tidy")
#endif()