cmake_minimum_required(VERSION 3.21)
project(TinyEngine)
set (CMAKE_CXX_STANDARD 17)
list(APPEND CMAKE_MESSAGE_CONTEXT ${PROJECT_NAME})

# Files
# ------------------------------------------------
set(SRC_FILES
    TinyEngine.h
    Core.h
    Main.h
    Application.h
    Application.cpp
    Window.h
    Window.cpp
    Camera.h
    Camera.cpp
    Renderer.h
    Renderer.cpp
    FileSystem.h 
    FileSystem.cpp 
    Shader.h
    Shader.cpp
    Program.h
    Program.cpp
    VertexBuffer.h
    VertexBuffer.cpp
    IndexBuffer.h
    IndexBuffer.cpp
    VertexArray.h
    VertexArray.cpp
    VertexBufferLayout.h
)
list(TRANSFORM SRC_FILES PREPEND "src/")

set(SHADER_FILES
    Light.frag
    Light.vert
)
list(TRANSFORM SHADER_FILES PREPEND "shaders/")


# Compile and Link
# ------------------------------------------------
add_library(${PROJECT_NAME} SHARED ${SRC_FILES} ${SHADER_FILES})
target_compile_definitions(TinyEngine PRIVATE TE_BUILD_DLL)

add_subdirectory(vendor)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glad
    glfw
    stbimage
    glm
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)