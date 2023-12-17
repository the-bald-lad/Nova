#pragma once

#include "Parser/Parser.h"

#include <string>


namespace Nova_Lang
{
    class Assembly_Generator
    {
    public:
        explicit Assembly_Generator(NodeExit root_node);

        ~Assembly_Generator() = default;

        [[nodiscard]] std::string generateAsm() const;  // Const is temp
    private:
        const NodeExit m_root;
    };
}
