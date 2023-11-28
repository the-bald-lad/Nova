#pragma once

#include <string>
#include <optional>


namespace Nova_Lang
{
    enum class TokenTypes
    {
        // Literals
        T_INT_LITERAL,
        T_FLOAT_LITERAL,
        T_STRING_LITERAL,

        // Operators
        T_PLUS,
        T_MINUS,
        T_MUL,
        T_DIV,
        T_MOD,

        // Keywords
        T_EXIT,

        // Brackets
        T_LBRACKET,
        T_RBRACKET,
        T_LCURLY,
        T_RCURLY,
        T_LSQUARE,
        T_RSQUARE,
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