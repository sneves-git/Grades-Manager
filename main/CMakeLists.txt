cmake_minimum_required(VERSION 3.15)
project(Project C)

set(CMAKE_C_STANDARD 11)

add_executable(Project main.c  main.h circularLists.c)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-Wall -Wextra")