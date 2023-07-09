cmake_minimum_required(VERSION 3.24)
project(rk3 C)

set(CMAKE_C_STANDARD 11)

add_executable(rk3 main.c graph.c graph.h)
