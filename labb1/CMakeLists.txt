cmake_minimum_required(VERSION 3.29)
project(labb1)

set(CMAKE_CXX_STANDARD 20)

add_executable(labb1 main.cpp
        parser.cpp
        parser.h
        lexer.cpp
        lexer.h
        ASTNode.cpp
        ASTNode.h
        print.h
        evaluate.h
)
