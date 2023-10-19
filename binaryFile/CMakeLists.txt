cmake_minimum_required(VERSION 3.16)
project(binaryFile C)

set(CMAKE_C_STANDARD 11)

add_executable(binaryFile main.c circularListTwoPriorities.c verificationFunctions.c main.h)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-Wall -Wextra")