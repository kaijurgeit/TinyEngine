cmake_minimum_required(VERSION 3.21)
project(TinyEngine)
set (CMAKE_CXX_STANDARD 17)
list(APPEND CMAKE_MESSAGE_CONTEXT ${PROJECT_NAME})

# Files
# ------------------------------------------------
set(SRC_FILES
    Application.h
    Application.cpp
    Camera.h
    Camera.cpp
    Core.h
    Event.h
    FileSystem.h 
    FileSystem.cpp 
    IndexBuffer.h
    IndexBuffer.cpp
    Main.h
    Material.cpp
    Material.h
    Material_Flat.cpp
    Material_Flat.h
    Mesh.cpp
    Mesh.h
    Model.cpp
    Model.h
    Renderer.h
    Renderer.cpp
    Shader.h
    Shader.cpp
    Texture.cpp
    Texture.h
    ShaderElement.h
    ShaderElement.cpp
    TinyEngine.h
    VertexArray.h
    VertexArray.cpp
    VertexBuffer.h
    VertexBuffer.cpp
    VertexBufferLayout.h
    Window.h
    Window.cpp
)
list(TRANSFORM SRC_FILES PREPEND "src/")

set(SHADER_FILES
    Flat.frag
    Flat.vert
    Model.frag
    Model.vert
    Phong.frag
    Phong.vert
    Texture.frag
    Texture.vert
)
list(TRANSFORM SHADER_FILES PREPEND "shaders/")


# Compile and Link
# ------------------------------------------------
add_library(${PROJECT_NAME} SHARED ${SRC_FILES} ${SHADER_FILES})
target_compile_definitions(TinyEngine PRIVATE TE_BUILD_DLL)
target_compile_definitions(TinyEngine PRIVATE GLFW_INCLUDE_NONE)

add_subdirectory(vendor)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glad
    glfw
    stbimage
    assimp
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    glm
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)