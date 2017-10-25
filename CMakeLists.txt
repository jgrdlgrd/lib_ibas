cmake_minimum_required(VERSION 3.6)
project(Labs)

list(APPEND CMAKE_C_FLAGS -std=c11)

include_directories(lib)
include_directories(.)

add_library(E4C lib/e4c/e4c.c)

FILE(GLOB_RECURSE LIB_1.0 lib_ibas/v1.0/*.c)
add_library(lib1.0 ${LIB_1.0})

FILE(GLOB_RECURSE LIB_1.5 lib_ibas/v1.5/*.c)
add_library(lib1.5 ${LIB_1.5})

FILE(GLOB_RECURSE LIB_1.9 lib_ibas/v1.9/*.c)
add_library(lib1.9 ${LIB_1.9})

FILE(GLOB_RECURSE LIB_2.0 lib_ibas/v2.0/*.[ch])
add_library(lib2.0 ${LIB_2.0})
#target_link_libraries(lib2.0 E4C)
#target_compile_definitions(lib2.0 PUBLIC USE_E4C)

FILE(GLOB_RECURSE LIB_3.0 lib_ibas/v3.0/*.c)
add_library(lib3.0 ${LIB_3.0})
target_link_libraries(lib3.0 E4C)
target_compile_definitions(lib3.0 PUBLIC USE_E4C)

add_executable(Unicode unicode-test.c)
target_link_libraries(Unicode lib1.0)

add_executable(Lab1.1 Lab1.1/lab1.23.c)
target_link_libraries(Lab1.1 lib1.0)
add_executable(Lab1.2 Lab1.2/lab2.23.c)
target_link_libraries(Lab1.2 lib1.0)
add_executable(Lab1.3 Lab1.3/lab3.23.c)
target_link_libraries(Lab1.3 lib1.0)
add_executable(Lab1.4 Lab1.4/lab4.23.c)
target_link_libraries(Lab1.4 lib1.5)

add_executable(Lab2.1 Lab2.1/lab2.1.1.c)
target_link_libraries(Lab2.1 lib1.9)
add_executable(Lab2.2 Lab2.2/lab2.2.1.c)
target_link_libraries(Lab2.2 lib2.0)

FILE(GLOB_RECURSE LAB2.3 Lab2.3/*.c)
add_executable(Lab2.3 ${LAB2.3})
target_link_libraries(Lab2.3 lib2.0)
