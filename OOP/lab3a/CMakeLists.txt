cmake_minimum_required(VERSION 3.16)
project(lab3a)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS -pthread)

add_executable(lab3a multiplication.cpp test.cpp)