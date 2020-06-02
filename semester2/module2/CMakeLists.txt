cmake_minimum_required(VERSION 3.14)
project(module2)

set(CMAKE_CXX_STANDARD 17)

add_executable(module2 main.cpp workers.h 1.h 2.h 3.h 4.h)