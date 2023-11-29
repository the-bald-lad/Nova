#include "Lexer.h"

#include <utility>


namespace Nova_Lang
{
    Lexer::Lexer(std::string input, std::string file_name)
    {
        this->input = std::move(input);
        this->file_name = std::move(file_name);  // Will be used later for error messages
        this->current_char = this->input[this->position];  // Set the current character to the first character in the input
        this->end_of_file = '\0';  // Null character termination
    }

    Lexer::~Lexer() = default;

    std::vector<Token> Lexer::Get_Tokens()
    {
         return this->tokens;
    }

    std::vector<Base_Error> Lexer::Get_Errors()
    {
        return this->errors;
    }

    void Lexer::Tokenize()
    {
        while (this->current_char != this->end_of_file)
        {
            std::string current_char_string = std::string(1, this->current_char);

            if (this->current_char == ' ' || this->current_char == '\t' || this->current_char == '\n')  // Is a whitespace character
            {
                this->Advance();
            }

            /* Literals and keywords */

            else if (std::isdigit(this->current_char))  // Is a digit literal
            {
                this->Create_Digit_Literal();
            }
            else if (std::isalpha(this->current_char))  // Is an identifier or keyword
            {
                this->Create_Identifier();
            }

            /* End of line*/
            else if (this->current_char == ';')
            {
                // If a semicolon is found, the statement is over.
                // This means that the buffer can be cleared.

                this->buffer.clear();

                this->tokens.push_back({ .type = TokenTypes::T_SEMICOLON });
                this->Advance();
            }

            /* Operators */

            else if (this->current_char == '+')
            {
                this->tokens.push_back({ .type = TokenTypes::T_PLUS });
                this->Advance();
            }
            else if (this->current_char == '-')
            {
                this->tokens.push_back({ .type = TokenTypes::T_MINUS });
                this->Advance();
            }
            else if (this->current_char == '*')
            {
                this->tokens.push_back({ .type = TokenTypes::T_MUL });
                this->Advance();
            }
            else if (this->current_char == '/')
            {
                this->tokens.push_back({ .type = TokenTypes::T_DIV });
                this->Advance();
            }
            else if (this->current_char == '%')
            {
                this->tokens.push_back({ .type = TokenTypes::T_MOD });
                this->Advance();
            }

            /* Brackets */

            else if (this->current_char == '(')
            {
                this->tokens.push_back({ .type = TokenTypes::T_LBRACKET });
                this->Advance();
            }
            else if (this->current_char == ')')
            {
                this->tokens.push_back({ .type = TokenTypes::T_RBRACKET });
                this->Advance();
            }
            else if (this->current_char == '{')
            {
                this->tokens.push_back({ .type = TokenTypes::T_LCURLY });
                this->Advance();
            }
            else if (this->current_char == '}')
            {
                this->tokens.push_back({ .type = TokenTypes::T_RCURLY });
                this->Advance();
            }
            else if (this->current_char == '[')
            {
                this->tokens.push_back({ .type = TokenTypes::T_LSQUARE });
                this->Advance();
            }
            else if (this->current_char == ']') {
                this->tokens.push_back({.type = TokenTypes::T_RSQUARE});
                this->Advance();
            }
            else
            {
                Illegal_Char_Error error = Illegal_Char_Error(this->current_char, this->file_name);
                errors.push_back(error);
            }
        }
    }

    // Advance to next character in input
    void Lexer::Advance()
    {
        this->position++;

        if (this->position > this->input.size() - 1)
            this->current_char = this->end_of_file;
        else
            this->current_char = this->input[this->position];
    }

    // Create either an integer or float token
    void Lexer::Create_Digit_Literal()
    {
        bool decimal_count = false;

        while (this->current_char != this->end_of_file && (this->digits_and_decimal.find(this->current_char) != std::string::npos)) {
            if (this->current_char == '.') {
                if (decimal_count)
                    break;
                decimal_count = true;
            }
            this->buffer += this->current_char;

            this->Advance();
        }


        if (decimal_count == 0)
        {
            int output_value = std::stoi(this->buffer);

            std::string output_value_string = std::to_string(output_value);

            this->tokens.push_back({ .type = TokenTypes::T_INT_LITERAL, .value = output_value_string });
        }
        else
        {
            float output_value = std::stof(this->buffer);

            std::string output_value_string = std::to_string(output_value);

            this->tokens.push_back({ .type = TokenTypes::T_FLOAT_LITERAL, .value = output_value_string });
        }

        this->buffer.clear();
    }

    // Create an identifier or keyword token
    void Lexer::Create_Identifier()
    {
        while (this->current_char != this->end_of_file && (std::isalnum(this->current_char) || this->current_char == '_'))
        {
            if (this->current_char == ' ')  // Temporary for testing
                break;
            this->buffer += this->current_char;

            this->Advance();
        }

        if (this->buffer == "exit")
            this->tokens.push_back({ .type = TokenTypes::T_EXIT });
        //else  // This needs fixing
        //    this->tokens.push_back({ .type = TokenTypes::T_STRING_LITERAL, .value = this->buffer });

        this->buffer.clear();
    }

    // Called from main, returns a pair of vectors containing the tokens and errors
    std::pair<std::vector<Token>, std::vector<Base_Error>> run_lexer(std::string& input, std::string& file_name)
    {
        Nova_Lang::Lexer lexer(input, file_name);
        lexer.Tokenize();

        return std::make_pair(lexer.Get_Tokens(), lexer.Get_Errors());
    }
}


