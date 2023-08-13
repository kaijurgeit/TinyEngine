cmake_minimum_required(VERSION 3.21)
project(TinyEngine)
set (CMAKE_CXX_STANDARD 17)
list(APPEND CMAKE_MESSAGE_CONTEXT ${PROJECT_NAME})


set(SRC_FILES
    TinyEngine.h
    Core.h
    Main.h
    Application.h
    Application.cpp
    Window.h
    Window.cpp
    Renderer.h
    Renderer.cpp
    FileSystem.h 
    FileSystem.cpp 
)

list(TRANSFORM SRC_FILES PREPEND "src/")

add_library(${PROJECT_NAME} SHARED ${SRC_FILES})
target_compile_definitions(TinyEngine PRIVATE TE_BUILD_DLL)

add_subdirectory(vendor)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glad
    glfw
)