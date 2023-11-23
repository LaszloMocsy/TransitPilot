cmake_minimum_required(VERSION 3.26)
project(TransitPilot C)

set(CMAKE_C_STANDARD 11)

add_executable(TransitPilot
        main.c
        lib/debugmalloc.h
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
        lib/econio.c
        menu.c
        menu.h
        lib/console.c
        lib/console.h
)
