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


#--------------------------------------------------------------------
# STB Image
#--------------------------------------------------------------------
FetchContent_Declare(
    stbimage
    GIT_REPOSITORY https://github.com/nothings/stb
    GIT_TAG 5736b15f7ea0ffb08dd38af21067c314d6a3aae9    # ?
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
)
FetchContent_MakeAvailable(stbimage)

add_library(stbimage INTERFACE)
target_include_directories(stbimage INTERFACE ${stbimage_SOURCE_DIR})
message("stbimage_SOURCE_DIR: ${stbimage_SOURCE_DIR}")


#--------------------------------------------------------------------
# GLM OpenGL Mathematics
#--------------------------------------------------------------------
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm
    GIT_TAG bf71a834948186f4097caa076cd2663c69a10e1e    # 0.9.9.8
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
)
FetchContent_MakeAvailable(glm)
