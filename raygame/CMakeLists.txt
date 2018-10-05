cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(maingame)

add_executable(maingame
    main.cpp
    tools.cpp
    )

target_link_libraries(maingame raylib)
