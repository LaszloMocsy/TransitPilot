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
        pathfinder.c
        pathfinder.h
        types/troute_t.c
        types/troute_t.h
)
