cmake_minimum_required(VERSION 3.26)
project(TransitPilot C)

set(CMAKE_C_STANDARD 11)

add_executable(TransitPilot
        main.c
        debugmalloc.h
        load.c
        load.h
        tstop_t.c
        tstop_t.h
        tline_t.c
        tline_t.h
        menu.c
        menu.h
        pathfinder.c
        pathfinder.h
        route_t.c
        route_t.h
)
