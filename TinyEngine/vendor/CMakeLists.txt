cmake_minimum_required(VERSION 3.21)

include(FetchContent)

#--------------------------------------------------------------------
# GLAD
#--------------------------------------------------------------------
FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad
    GIT_TAG a5ca31c88a4cc5847ea012629aff3690f261c7c4    # 0.1.34.
)
FetchContent_MakeAvailable(glad)
message("glad_SOURCE_DIR: ${glad_SOURCE_DIR}")

#--------------------------------------------------------------------
# GLFW
#--------------------------------------------------------------------
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw
    GIT_TAG 814b7929c5add4b0541ccad26fb81f28b71dc4d8    # 3.3.4
)
FetchContent_MakeAvailable(glfw)