cmake_minimum_required(VERSION 3.20)
project(GameOfLifeOnGraphsCPP)

set(CMAKE_CXX_STANDARD 14)

add_executable(GameOfLifeOnGraphsCPP main.cpp include/gol.h include/graph.h source/gol.cpp source/graph.cpp)
include_directories(./include)