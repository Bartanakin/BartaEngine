add_executable(${RUN_TEST_NAME}
    main.cpp
    Sandbox.cpp
)

target_link_libraries(${RUN_TEST_NAME} PUBLIC
        sfml-graphics
        ${LIBRARY_NAME}
)

if(WIN32)
    add_custom_command(
        TARGET ${RUN_TEST_NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${RUN_TEST_NAME}>
        VERBATIM)
endif()

target_include_directories(${RUN_TEST_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/include")

add_test(NAME VectorOutput COMMAND ${RUN_TEST_NAME})