cmake_minimum_required(VERSION 3.21)
project(TinyEngine)
set (CMAKE_CXX_STANDARD 17)
list(APPEND CMAKE_MESSAGE_CONTEXT ${PROJECT_NAME})

set(SRC_FILES
    TinyEngine.h
    Core.h
    Application.h
    Application.cpp
)

list(TRANSFORM SRC_FILES PREPEND "src/")

add_library(${PROJECT_NAME} SHARED ${SRC_FILES})
target_compile_definitions(TinyEngine PRIVATE TE_BUILD_DLL)

add_subdirectory(external)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glad
    glfw
)

option(BuildTests OFF)
if(BuildTests)
    enable_testing()
    add_subdirectory(test)
endif()

add_subdirectory(application)