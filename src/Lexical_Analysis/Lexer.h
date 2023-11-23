#pragma once

#include "Token.h"
#include "../Error_Classes/Errors.h"

#include <string>
#include <vector>

namespace Nova_Lang {

    class Lexer {
    public: // Lexer public methods
        explicit Lexer(std::string input, std::string file_name);

        ~Lexer();

        void Tokenize();

        std::vector<Token> Get_Tokens();

        std::vector<Base_Error> Get_Errors();

    private: // Lexer public attributes
        // Token constants
        std::string T_INT      = "INT";
        std::string T_FLOAT    = "FLOAT";
        std::string T_PLUS     = "PLUS";
        std::string T_MINUS    = "MINUS";
        std::string T_MUL      = "MUL";
        std::string T_DIV      = "DIV";
        std::string T_MOD      = "MOD";
        std::string T_LBRACKET = "LBRACKET";
        std::string T_RBRACKET = "RBRACKET";
        std::string DIGITS     = "0123456789";

        // Lexer variables
        std::string input;
        char end_of_file;

        // File information
        std::string file_name;

        // Lexer information
        int position = 0;
        char current_char;

        // Tokens
        std::vector<Token> tokens;  // Temporary, will be replaced with a vector of Token objects

        // Errors
        std::vector<Base_Error> errors;
    private: // Lexer private methods
        void Advance();

        void Make_Number();
    };

    std::vector<Token> run_lexer(std::string&, std::string&);
}
