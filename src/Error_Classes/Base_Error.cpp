#include "Errors.h"

namespace programming_language_name
{
    Base_Error::Base_Error(std::string error_name, std::string details, std::string file_name)
    {
        this->super_name = std::move(error_name);
        this->super_details = std::move(details);
        this->super_file_name = std::move(file_name);
    }

    std::string Base_Error::As_String() const
    {
        return this->super_file_name + ": " + this->super_details;
    }
}