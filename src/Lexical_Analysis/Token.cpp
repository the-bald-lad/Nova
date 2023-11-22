#include "Token.h"

#include <utility>

namespace programming_language_name
{
    Token::Token()
    {
        this->type = "NULL";
        this->value = "NULL";
    }

    Token::Token(std::string input_type)
    {
        this->type = std::move(input_type);
        this->value = "NULL";
    }

    Token::Token(std::string input_type, std::string input_value)
    {
        this->type = std::move(input_type);
        this->value = std::move(input_value);
    }

    Token::~Token() = default;

    std::string Token::Represent()
    {
        if (this->value == "NULL")
            return this->type;
        else
            return std::string(this->type + ":" + this->value);
    }
}