cmake_minimum_required(VERSION 3.21)
project(Application)
set (CMAKE_CXX_STANDARD 17)
list(APPEND CMAKE_MESSAGE_CONTEXT ${PROJECT_NAME})


set(SRC_FILES
    Main.cpp
)

list(TRANSFORM SRC_FILES PREPEND "src/")
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(
    ${PROJECT_NAME} PRIVATE "../src"
)

target_link_libraries(${PROJECT_NAME} 
    TinyEngine
)

# add_custom_command(
#     TARGET Application POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different
#             $<TARGET_RUNTIME_DLLS:Application> $<TARGET_FILE_DIR:Application>
#     COMMAND_EXPAND_LISTS
# )