cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(aieraygame)

set(CMAKE_CXX_STANDARD 14)

link_directories(thirdparty/raylib/lib/x64)

find_library(raylib
    NAMES raylib)

include_directories(thirdparty/raylib)

add_subdirectory(raygame)
