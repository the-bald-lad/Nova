#include "Errors.h"

namespace Nova_Lang
{
    Illegal_Char_Error::Illegal_Char_Error(const char c, std::string& file_name)
        : Base_Error("Illegal Character", std::string(1, c), std::move(file_name)) {}

    std::string Illegal_Char_Error::As_String() const
    {
        return this->super_name + ": " + this->super_details + " in " + this->super_file_name;
    }
}