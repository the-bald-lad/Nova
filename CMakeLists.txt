cmake_minimum_required(VERSION 3.26)
project(programming_language)

set(CMAKE_CXX_STANDARD 17)

add_executable(programming_language src/main.cpp
        "src/Lexical_Analysis/Lexer.h"
        "src/Lexical_Analysis/Lexer.cpp"
        "src/Lexical_Analysis/Token.cpp"
        "src/Lexical_Analysis/Token.h"
        "src/Error_Classes/Base_Error.cpp"
        "src/Error_Classes/Errors.h"
        "src/Error_Classes/Illegal_Char_Error.cpp"
)
