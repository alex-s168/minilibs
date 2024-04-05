cmake_minimum_required(VERSION 3.28)
project(minifmt C)

set(CMAKE_C_STANDARD 99)

add_executable(minifmt test.c
        minifmt.h)
