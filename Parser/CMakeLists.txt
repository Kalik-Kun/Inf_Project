cmake_minimum_required(VERSION 3.12)
project(Parser)

set(CMAKE_CXX_STANDARD 14)

#add_executable(Parser main.cpp)
add_executable(Parser main.cpp Source/Source.cpp Headers/Source.h Source/AbstractSyntaxTree.cpp
        Headers/AbstractSyntaxTree.h Headers/debug.h Source/Parser.cpp Headers/Parser.h Source/Lexer.cpp Headers/Lexer.h Headers/Defines.h)