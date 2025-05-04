enable_testing()

add_subdirectory(Dynamics)
add_subdirectory(Objects)
add_subdirectory(Utilities)

target_link_libraries(
        ${TESTS_TARGET_NAME}
        ${LIBRARY_NAME}
)
target_link_libraries(
        ${TESTS_TARGET_NAME}
        GTest::gtest_main
        GTest::gmock
)

include(GoogleTest)
