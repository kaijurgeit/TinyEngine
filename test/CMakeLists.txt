cmake_minimum_required(VERSION 3.21)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
option(INSTALL_GTEST "Enable installation of googletest." OFF)
include(FetchContent)
FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git # v1.14.0
        GIT_TAG f8d7d77c06936315286eb55f8de22cd23c188571)
FetchContent_MakeAvailable(googletest)


project(Test_TinyEngine)

set(SRC_FILES 
    MyLibrary_Test.cpp
    MyOtherLibrary_Test.cpp
)

enable_testing()

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(
    ${PROJECT_NAME} PRIVATE "../src"
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    gtest_main
    TinyEngine
)

add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
)

include(GoogleTest)


add_custom_command(
    TARGET Test_TinyEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:Test_TinyEngine> $<TARGET_FILE_DIR:Test_TinyEngine>
    COMMAND_EXPAND_LISTS
)