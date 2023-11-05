cmake_minimum_required(VERSION 3.26)
project(TransitPilot C)

set(CMAKE_C_STANDARD 11)

add_executable(TransitPilot
        main.c
        debugmalloc.h
        load.c
        load.h
        transit.c
        transit.h
)
