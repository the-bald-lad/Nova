#include "Errors.h"

namespace programming_language_name
{
    Illegal_Char_Error::Illegal_Char_Error(char c, std::string file_name)
        : Base_Error("Illegal Character", std::string(1, c), std::move(file_name))
    {
    }

    std::string Illegal_Char_Error::As_String() const
    {
        return this->super_name + ": " + this->super_details + " in " + this->super_file_name;
    }
}