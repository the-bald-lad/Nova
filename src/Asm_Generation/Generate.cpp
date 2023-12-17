#include "Generate.h"

#include <utility>
#include <sstream>

namespace Nova_Lang
{
    Assembly_Generator::Assembly_Generator(Nova_Lang::NodeExit root_node)
        : m_root(std::move(root_node))
    {
    }

    std::string Assembly_Generator::generateAsm() const
    {
        std::stringstream asm_output;

        asm_output << "global _start\n";
        asm_output << "_start\n";
        asm_output << "    mov rax, 60\n";
        asm_output << "    mov rdi, " << m_root.expression.int_literal.value.value() << "\n";
        asm_output << "    syscall";

        return asm_output.str();
    }
}