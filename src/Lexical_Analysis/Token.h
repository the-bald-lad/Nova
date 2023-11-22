#pragma once

#include <string>

namespace programming_language_name
{
    class Token
    {
    public:
        explicit Token();
        explicit Token(std::string input_type);
        Token(std::string input_type, std::string input_value);

        ~Token();

        std::string Represent();
    private:
        std::string type;
        std::string value;
    };
}