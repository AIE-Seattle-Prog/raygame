cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(raygame)

set(CMAKE_CXX_STANDARD 14)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH_64 TRUE)
    set(PROCESSOR_ARCH "x64")
else()
    set(ARCH_64 FALSE)
    set(PROCESSSOR_ARCH "x86")
endif()

# setup arch dependent paths
if(ARCH_64)
    set(RAYLIB_PATH thirdparty/raylib/lib/x64)
else()
    set(RAYLIB_PATH thirdparty/raylib/lib/x86)
endif()

link_directories(${RAYLIB_PATH})

find_library(raylib
    NAMES raylib)

include_directories(thirdparty/raylib)

add_subdirectory(raygame)
