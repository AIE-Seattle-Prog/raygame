cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(test)

add_library(test
    test.h
    test.cpp)
#target_include_directories(test INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})