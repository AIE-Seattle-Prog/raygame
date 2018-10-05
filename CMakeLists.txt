cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(raygame)

set(CMAKE_CXX_STANDARD 14)

# determine architecture (i.e. x64? x86?)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH_DIR_EXT x64)
else()
    set(ARCH_DIR_EXT x86)
endif()

# raylib
# todo: look into INSTALL_INTERFACE

add_library(raylib STATIC IMPORTED "raylib.h")
set_target_properties(raylib
    PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/raylib/lib/${ARCH_DIR_EXT}/raylib.lib 
    INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/raylib/
    PUBLIC_HEADER "raylib.h"
)

# add project directory
add_subdirectory(raygame)
