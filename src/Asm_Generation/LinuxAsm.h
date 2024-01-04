#pragma once

#include "Parser/Parser.h"

#include <string>


namespace Nova_Lang
{
    class Assembly_Generator
    {
    public:
        explicit Assembly_Generator(std::vector<std::any> tree);

        ~Assembly_Generator() = default;

        [[nodiscard]] std::string generateAsm() const;  // Const is temp
    private:
        const std::vector<std::any> m_tree;
    };
}
