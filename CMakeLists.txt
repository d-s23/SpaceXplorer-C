cmake_minimum_required(VERSION 3.21)
project(sapcexplorer C)

set(CMAKE_C_STANDARD 99)

add_executable(sapcexplorer main.c gameFunctions.h gameFunctions.c)
