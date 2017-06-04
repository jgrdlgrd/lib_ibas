cmake_minimum_required(VERSION 3.6)
project(Labs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

include_directories(lib)
include_directories(.)

set(E4C lib/e4c/e4c.h lib/e4c/e4c.c)

FILE(GLOB_RECURSE LIB_1.0 lib_ibas/v1.0/*.[ch])

FILE(GLOB_RECURSE LIB_1.5 lib_ibas/v1.5/*.[ch])

FILE(GLOB_RECURSE LIB_1.9 lib_ibas/v1.9/*.[ch])

FILE(GLOB_RECURSE LIB_2.0 lib_ibas/v2.0/*.[ch])
#set(LIB_2.0 ${LIB_2.0} ${E4C})

FILE(GLOB_RECURSE LIB_3.0 lib_ibas/v3.0/*.[ch])
set(LIB_3.0 ${LIB_3.0} ${E4C})

add_executable(Unicode unicode-test.c ${LIB_1.0})

add_executable(Lab1.1 Lab1.1/lab1.23.c ${LIB_1.0})
add_executable(Lab1.2 Lab1.2/lab2.23.c ${LIB_1.0})
add_executable(Lab1.3 Lab1.3/lab3.23.c ${LIB_1.0})
add_executable(Lab1.4 Lab1.4/lab4.23.c ${LIB_1.5})

add_executable(Lab2.1 Lab2.1/lab2.1.1.c ${LIB_1.9})
add_executable(Lab2.2 Lab2.2/lab2.2.1.c ${LIB_2.0})

FILE(GLOB_RECURSE LAB2.3 Lab2.3/*.[ch])
add_executable(Lab2.3 ${LAB2.3} ${LIB_2.0})
