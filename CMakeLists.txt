cmake_minimum_required(VERSION 3.26)
project(nova)

set(CMAKE_CXX_STANDARD 17)

include_directories(src/)

add_executable(nova src/main.cpp
        "src/Lexer/Lexer.h"
        "src/Lexer/Lexer.cpp"
        "src/Lexer/Token.h"
        "src/Errors/Base_Error.cpp"
        "src/Errors/Errors.h"
        "src/Errors/Parser_Error.cpp"
        "src/Errors/Illegal_Char_Error.cpp"
        "src/Parser/Parser.cpp"
        "src/Parser/Parser.h"
        "src/Asm_Generation/Generate.cpp"
        "src/Asm_Generation/Generate.h"
        "src/Timing/Timer.cpp"
        "src/Timing/Timer.h"
)
