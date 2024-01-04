#pragma once

#include <string>
#include <optional>


namespace Nova_Lang
{
    enum class TokenTypes
    {
        // Variable types
        T_INT_VAR = 0,
        T_FLOAT_VAR,
        T_STRING_VAR,

        // Literals (Should have a value associated with them)
        T_INT_LITERAL,
        T_FLOAT_LITERAL,
        T_STRING_LITERAL,

        // Operators
        T_PLUS,
        T_MINUS,
        T_MUL,
        T_DIV,
        T_MOD,

        // Brackets
        T_LBRACKET,
        T_RBRACKET,
        T_LCURLY,
        T_RCURLY,
        T_LSQUARE,
        T_RSQUARE,

        // End of statement
        T_SEMICOLON,

        // Keywords
        T_EXIT,
        T_PRINT,
    };

    struct Token
    {
        TokenTypes type {};
        std::optional<std::string> value {};

        [[nodiscard]] std::string Represent() const
        {
            return "Token(" + std::to_string(static_cast<int>(this->type)) + ", " + this->value.value_or("") + ")";
        }
    };
}