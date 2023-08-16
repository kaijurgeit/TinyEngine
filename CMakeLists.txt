cmake_minimum_required(VERSION 3.21)
project(TinyEngine)
add_subdirectory(TinyEngine)

option(BuildTests "Build google tests" ON)
if(BuildTests)
    enable_testing()
    add_subdirectory(Test)
endif()

option(BuildApp "Build the example application" ON)
if(BuildApp)
    enable_testing()
    add_subdirectory(App)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT App)
endif()

set(CMAKE_BUILD_TYPE Debug)