cmake_minimum_required(VERSION 3.19)
project(kotlin_lexer)

set(CMAKE_CXX_STANDARD 20)

add_executable(kotlin_lexer main.cpp KotlinLexer.cpp KotlinLexer.hpp)