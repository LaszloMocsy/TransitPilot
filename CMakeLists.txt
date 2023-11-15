cmake_minimum_required(VERSION 3.26)
project(TransitPilot C)

set(CMAKE_C_STANDARD 11)

add_executable(TransitPilot
        main.c
        debugmalloc.h
        load.c
        load.h
        types/tstop_t.c
        types/tstop_t.h
        types/tline_t.c
        types/tline_t.h
        menu.c
        menu.h
        pathfinder.c
        pathfinder.h
        types/route_t.c
        types/route_t.h
)
