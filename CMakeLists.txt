cmake_minimum_required(VERSION 3.26)
project(nova_lang)

set(CMAKE_CXX_STANDARD 17)

include_directories(src/)

add_executable(nova_lang src/main.cpp
        "src/Lexical_Analysis/Lexer.h"
        "src/Lexical_Analysis/Lexer.cpp"
        "src/Lexical_Analysis/Token.h"
        "src/Error_Classes/Base_Error.cpp"
        "src/Error_Classes/Errors.h"
        "src/Error_Classes/Illegal_Char_Error.cpp"
)
