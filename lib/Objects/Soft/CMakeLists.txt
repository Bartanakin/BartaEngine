target_sources(${LIBRARY_NAME} PUBLIC
    Mesh.cpp
    TetrahedralElement.cpp
    SoftObject.cpp
)

add_subdirectory(MshParser)
add_subdirectory(MshLoader)
