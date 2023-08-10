cmake_minimum_required(VERSION 3.1)
project(TinyEngine)
set (CMAKE_CXX_STANDARD 17)
list(APPEND CMAKE_MESSAGE_CONTEXT ${PROJECT_NAME})

set(SRC_FILES
    MyLibrary.cpp
    MyLibrary.h
)

list(TRANSFORM SRC_FILES PREPEND "src/")

add_library(${PROJECT_NAME} STATIC ${SRC_FILES})

