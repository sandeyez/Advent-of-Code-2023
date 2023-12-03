cmake_minimum_required(VERSION 3.26)
project(Advent_of_Code_2023)

set(CMAKE_CXX_STANDARD 14)

add_executable(Advent_of_Code_2023
        utils.cpp
        day-01/day01.cpp
        day-02/day02.cpp
        main.cpp
        day-02/day02.h
        day-01/day01.h
        day-03/day03.h
        day-03/day03.cpp
)
