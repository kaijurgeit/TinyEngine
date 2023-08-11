cmake_minimum_required(VERSION 3.21)
add_subdirectory(TinyEngine)

option(BuildTests OFF)
if(BuildTests)
    enable_testing()
    add_subdirectory(Test)
endif()

option(BuildApp ON)
if(BuildApp)
    enable_testing()
    add_subdirectory(App)
endif()