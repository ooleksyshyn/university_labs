cmake_minimum_required(VERSION 3.14)
project(lab1)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab1 graph.h object.cpp object.h exceptions.h exceptions.cpp test.cpp others.hpp others.cpp)