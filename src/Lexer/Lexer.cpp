#include "Lexer.h"

#include <utility>


namespace Nova_Lang
{
    Lexer::Lexer(std::string input, std::string file_name)
    {
        m_input = std::move(input);
        m_file_name = std::move(file_name);  // Will be used later for error messages
        m_current_char = m_input[m_position];  // Set the current character to the first character in the m_input
        m_end_of_file = '\0';  // Null character termination
    }

    Lexer::~Lexer() = default;

    std::vector<Token> Lexer::Get_Tokens()
    {
         return m_tokens;
    }

    void Lexer::Tokenize()
    {
        while (m_current_char != m_end_of_file)
        {
            std::string current_char_string = std::string(1, m_current_char);

            if (m_current_char == ' ' || m_current_char == '\t' || m_current_char == '\n')  // Is a whitespace character
            {
                Advance();
            }

            /* Literals and keywords */

            else if (std::isdigit(m_current_char))  // Is a digit literal
            {
                Create_Digit_Literal();
            }
            else if (std::isalpha(m_current_char))  // Is an identifier or keyword
            {
                Create_Identifier();
            }

            /* End of line*/
            else if (m_current_char == ';')
            {
                // If a semicolon is found, the statement is over.
                // This means that the m_buffer can be cleared.

                m_buffer.clear();

                m_tokens.push_back({ .type = TokenTypes::T_SEMICOLON });
                Advance();
            }

            /* Operators */

            else if (m_current_char == '+')
            {
                m_tokens.push_back({ .type = TokenTypes::T_PLUS });
                Advance();
            }
            else if (m_current_char == '-')
            {
                m_tokens.push_back({ .type = TokenTypes::T_MINUS });
                Advance();
            }
            else if (m_current_char == '*')
            {
                m_tokens.push_back({ .type = TokenTypes::T_MUL });
                Advance();
            }
            else if (m_current_char == '/')
            {
                m_tokens.push_back({ .type = TokenTypes::T_DIV });
                Advance();
            }
            else if (m_current_char == '%')
            {
                m_tokens.push_back({ .type = TokenTypes::T_MOD });
                Advance();
            }

            /* Brackets */

            else if (m_current_char == '(')
            {
                m_tokens.push_back({ .type = TokenTypes::T_LBRACKET });
                Advance();
            }
            else if (m_current_char == ')')
            {
                m_tokens.push_back({ .type = TokenTypes::T_RBRACKET });
                Advance();
            }
            else if (m_current_char == '{')
            {
                m_tokens.push_back({ .type = TokenTypes::T_LCURLY });
                Advance();
            }
            else if (m_current_char == '}')
            {
                m_tokens.push_back({ .type = TokenTypes::T_RCURLY });
                Advance();
            }
            else if (m_current_char == '[')
            {
                m_tokens.push_back({ .type = TokenTypes::T_LSQUARE });
                Advance();
            }
            else if (m_current_char == ']')
            {
                m_tokens.push_back({.type = TokenTypes::T_RSQUARE});
                Advance();
            }
            else
            {
                Illegal_Char_Error error = Illegal_Char_Error(this->m_current_char, this->m_file_name);
                error_buffer.push_back(error);
            }
        }
    }

    // Advance to next character in m_input
    void Lexer::Advance(int offset)
    {
        m_position++;

        if (m_position > m_input.size() - 1)
            m_current_char = m_end_of_file;
        else
            m_current_char = m_input[m_position + offset];
    }

    // Create either an integer or float token
    void Lexer::Create_Digit_Literal()
    {
        bool decimal_count = false;

        while (m_current_char != m_end_of_file && (m_digits_and_decimal.find(m_current_char) != std::string::npos)) {
            if (m_current_char == '.') {
                if (decimal_count)
                    break;
                decimal_count = true;
            }
            m_buffer += m_current_char;

            Advance();
        }


        if (decimal_count == 0)
        {
            int64_t output_value = std::stoi(m_buffer);

            std::string output_value_string = std::to_string(output_value);

            m_tokens.push_back({ .type = TokenTypes::T_INT_LITERAL, .value = output_value_string });
        }
        else
        {
            float output_value = std::stof(m_buffer);

            std::string output_value_string = std::to_string(output_value);

            m_tokens.push_back({ .type = TokenTypes::T_FLOAT_LITERAL, .value = output_value_string });
        }

        m_buffer.clear();
    }

    void Lexer::Parse_StringVar_Name()
    {
        m_buffer.clear();

        // Remove space character
        Advance();

        while (m_current_char != m_end_of_file && (std::isalnum(m_current_char) || m_current_char == '_'))
        {
            if (m_current_char == ' ')
                break;
            m_buffer += m_current_char;

            Advance();
        }
    }

    void Lexer::Parse_StringVar_Contents()
    {
        // Remove space character
        Advance();

        // Remove equals
        if (m_current_char == '=')
            Advance();

        int8_t quotes_count = 0;
        while (m_current_char != m_end_of_file)
        {
            if (2 <= quotes_count)
                break;

            if (m_current_char == '"')
            {
                quotes_count++;
                Advance();
                continue;
            }

            m_buffer += m_current_char;

            Advance();
        }
    }

    // Create an identifier or keyword token
    void Lexer::Create_Identifier()
    {
        while (m_current_char != m_end_of_file && (std::isalnum(m_current_char) || m_current_char == '_'))
        {
            if (m_current_char == ' ')
                break;
            m_buffer += m_current_char;

            Advance();
        }

        // Keyword check
        if (m_buffer == "exit")  // Exit keyword
        {
            m_tokens.push_back({ .type = TokenTypes::T_EXIT });
        }
        else if (m_buffer == "string")  // string variable assignment
        {
            // TODO: Change token values to be able to be another token
            Parse_StringVar_Name();

            m_tokens.push_back({ .type = TokenTypes::T_STRING_VAR, .value = m_buffer });

            Parse_StringVar_Contents();

            m_tokens.push_back({ .type = TokenTypes::T_STRING_LITERAL, .value = m_buffer });
        }
        else
        {
            // TODO: Create illegal keyword error subclass
            Illegal_Char_Error error = Illegal_Char_Error(this->m_current_char, this->m_file_name);  // TEMP
            error_buffer.push_back(error);
        }

        m_buffer.clear();
    }

    // Called from main, returns a pair of vectors containing the m_tokens and errors
    std::vector<Token> run_lexer(std::string& input, std::string& file_name)
    {
        Nova_Lang::Lexer lexer(input, file_name);
        lexer.Tokenize();

        return lexer.Get_Tokens();
    }
}


