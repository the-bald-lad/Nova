#include <utility>

#include "Errors.h"

namespace Nova_Lang
{
    Parser_Error::Parser_Error(const Token& token, std::string name, std::string file_name)
        : Base_Error(std::move(name), token.Represent(), std::move(file_name))
    {
    }

    std::string Parser_Error::As_String() const
    {
        return this->super_name + ": " + this->super_details + " in " + this->super_file_name;
    }
}