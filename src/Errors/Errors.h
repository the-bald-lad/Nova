#pragma once

#include "Lexer/Token.h"

#include <string>
#include <vector>

namespace Nova_Lang
{
    struct Error_Types
    {
        const std::string ILLEGAL_CHAR      = "Illegal Character";
        const std::string UNEXPECTED_CHAR   = "Unexpected Character";
        const std::string INVALID_SYNTAX    = "Invalid Syntax";
        const std::string RUNTIME_ERROR     = "Runtime Error";
    };


    struct Base_Error
    {
        Base_Error(std::string error_name, std::string details, std::string file_name);

        virtual ~Base_Error() = default;

        [[nodiscard]] virtual std::string As_String() const;

        std::string super_name;
        std::string super_details;
        std::string super_file_name;
    };

    struct Illegal_Char_Error : public Base_Error
    {
        Illegal_Char_Error(char c, std::string file_name);

        ~Illegal_Char_Error() override = default;

        [[nodiscard]] std::string As_String() const override;
    };

    struct Parser_Error : public Base_Error
    {
        Parser_Error(const Token& token, std::string name, std::string file_name);

        ~Parser_Error() override = default;

        [[nodiscard]] std::string As_String() const override;
    };

    inline std::vector<Base_Error> error_buffer;
}