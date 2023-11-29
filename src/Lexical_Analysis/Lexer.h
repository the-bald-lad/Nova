#pragma once

#include "Token.h"
#include "Error_Classes/Errors.h"

#include <vector>

namespace Nova_Lang
{
    class Lexer
    {
    public: // Lexer public methods
        explicit Lexer(std::string input, std::string file_name);

        ~Lexer();

        void Tokenize();

        std::vector<Token> Get_Tokens();

        std::vector<Base_Error> Get_Errors();

    private: // Lexer public attributes
        // Lexer variables
        std::string input;
        char end_of_file;

        // File information
        std::string file_name;

        // Lexer information
        int position = 0;
        char current_char;

        std::string digits = "0123456789";
        std::string digits_and_decimal = digits + '.';

        // Lexer Buffer
        std::string buffer;

        // Tokens
        std::vector<Token> tokens;

        // Errors
        std::vector<Base_Error> errors;
    private: // Lexer private methods
        void Advance();

        void Create_Digit_Literal();

        void Create_Identifier();
    };

    std::pair<std::vector<Token>, std::vector<Base_Error>> run_lexer(std::string&, std::string&);
}
