cmake_minimum_required(VERSION 3.26)
project(TransitPilot C)

set(CMAKE_C_STANDARD 11)

add_executable(TransitPilot
        main.c
        debugmalloc.h
        load.c
        load.h
        tstop.c
        tstop.h
        tline.c
        tline.h
        menu.c
        menu.h
)
