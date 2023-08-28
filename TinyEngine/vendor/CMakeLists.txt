cmake_minimum_required(VERSION 3.21)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build GLFW Docs")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build GLFW Examples")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build GLFW Tests")
set(GLFW_INSTALL OFF CACHE BOOL "Build GLFW Install Target")
set(ASSIMP_BUILD_DOCS OFF CACHE BOOL "Build Assimp Docs")
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "Build Assimp Tests")
set(ASSIMP_INSTALL OFF CACHE BOOL "Build Assimp Install Target")
set(ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT OFF CACHE BOOL "Build all Assimp Exporters by default")
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF CACHE BOOL "Build all Importers Exporters by default")
set(ASSIMP_BUILD_OBJ_IMPORTER ON CACHE BOOL "Build OBJ Importer")
# set(ASSIMP_BUILD_FBX_IMPORTER ON CACHE BOOL "Build FBX Importer")


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



#--------------------------------------------------------------------
# Open Asset Import Library (assimp)
#--------------------------------------------------------------------
FetchContent_Declare(
    assimp
    GIT_REPOSITORY https://github.com/assimp/assimp
    GIT_TAG 9519a62dd20799c5493c638d1ef5a6f484e5faf1    # 5.2.5
)
FetchContent_MakeAvailable(assimp)


set(Solution_Folder "vendor")
if(TARGET glad-generate-files)    
    set_target_properties(glad-generate-files PROPERTIES FOLDER ${Solution_Folder})
endif()
if(TARGET glad)    
    set_target_properties(glad PROPERTIES FOLDER ${Solution_Folder})
endif()
if(TARGET glfw)    
    set_target_properties(glfw PROPERTIES FOLDER ${Solution_Folder})
endif()
if(TARGET stbimage)    
    set_target_properties(stbimage PROPERTIES FOLDER ${Solution_Folder})
endif()
if(TARGET glm)    
    set_target_properties(glm PROPERTIES FOLDER ${Solution_Folder})
endif()
if(TARGET unit)    
    set_target_properties(unit PROPERTIES FOLDER ${Solution_Folder})
endif()
if(TARGET assimp)    
    set_target_properties(assimp PROPERTIES FOLDER ${Solution_Folder})
endif()
if(TARGET UpdateAssimpLibsDebugSymbolsAndDLLs)    
    set_target_properties(UpdateAssimpLibsDebugSymbolsAndDLLs PROPERTIES FOLDER ${Solution_Folder})
endif()