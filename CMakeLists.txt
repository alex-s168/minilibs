cmake_minimum_required(VERSION 3.28)
project(minilibs C)

set(CMAKE_C_STANDARD 99)

add_executable(minilibs test.c
        miniconf.h
        filelib.h
        memlib.h
        minifmt.h
        minitab.h
        cli.h)

target_link_libraries(minilibs m)
