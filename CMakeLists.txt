cmake_minimum_required(VERSION 3.15)
project(INF432 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(INF432
        cnfMaker.c
        dimacs.c
        dimacs.h
        generation.c
        generation.h
        grid.c
        grid.h
        gridGeneration.c
        logic.c
        logic.h
        main.c
        satTo3sat.c
        solutionReader.c
        solver.c
        solver.h
        walkSat.c)
