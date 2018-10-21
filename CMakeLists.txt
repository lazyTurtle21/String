cmake_minimum_required(VERSION 3.8)
project(lab2)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c my_str_t.h)
add_executable(lab2 ${SOURCE_FILES})
