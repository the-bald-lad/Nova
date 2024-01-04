#pragma once

#include "Token.h"
#include "Errors/Errors.h"

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

    private: // Lexer public attributes
        // Lexer variables
        std::string m_input;
        char m_end_of_file;

        // File information
        std::string m_file_name;

        // Lexer information
        int m_position = 0;
        char m_current_char;

        std::string m_digits = "0123456789";
        std::string m_digits_and_decimal = m_digits + '.';

        // Lexer Buffer
        std::string m_buffer;

        // Tokens
        std::vector<Token> m_tokens;
    private: // Lexer private methods
        void Advance(int offset = 0);

        void Parse_StringVar_Name();

        void Parse_StringVar_Contents();

        void Create_Digit_Literal();

        void Create_Identifier();

        void Create_String_Literal();
    };

    std::vector<Token> run_lexer(const std::string&, const std::string&);
}
