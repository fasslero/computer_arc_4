cmake_minimum_required(VERSION 3.8)
project(computer_arc_4)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp excecute.cpp cache.cpp cache.h)
add_executable(computer_arc_4 ${SOURCE_FILES} excecute.cpp cache.cpp cache.h)