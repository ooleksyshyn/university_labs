cmake_minimum_required(VERSION 3.15)
project(lab3)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab3 main.cpp struct.hpp NodeTools.hpp Splay.hpp Splay.tpp
        SplayTree.hpp SplayTree.tpp SplayTreeIterator.tpp SplayTreeNode.hpp)