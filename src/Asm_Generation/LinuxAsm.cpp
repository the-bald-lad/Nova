// TODO: FIX EVERYTHING

#include "LinuxAsm.h"

#include <utility>
#include <sstream>

namespace Nova_Lang
{
    Assembly_Generator::Assembly_Generator(std::vector<std::any> tree)
        : m_tree(std::move(tree))
    {
    }

    std::string Assembly_Generator::generateAsm() const
    {
        bool exit_present = false;
        bool string_buffers_needed = false;

        std::vector<std::any> string_buffers;

        std::stringstream asm_output;

        for (const std::any& node : m_tree)
        {
            // Start of ASM
            asm_output << "global _start\n";
            asm_output << "_start\n";

            if (node.has_value() && node.type() == typeid(NodeExit))
            {
                asm_output << "    mov rax, 60\n";  // Kernal code for exit
                asm_output << "    mov rdi, " << std::any_cast<NodeExit>(node).expression.int_literal.value.value() << "\n";
                asm_output << "    syscall\n";

                exit_present = true;
                break;
            }

            if (node.has_value() && node.type() == typeid(NodePrint))
            {
                asm_output << "    mov rax, 1";  // Kernal code for standard out
                asm_output << "    mov rdi, 1";
                asm_output << "    lea rsi, [" << std::any_cast<NodePrint>(node).contents.buffer_name << "]\n";
                asm_output << "    mov rdx, " << std::any_cast<NodePrint>(node).contents.length << "\n";
                asm_output << "    syscall\n";

                string_buffers_needed = true;
                string_buffers.push_back(node);
            }
        }

        if (!exit_present)
        {
            asm_output << "    mov rax, 60\n";  // Kernal code for exit
            asm_output << "    mov rdi, 1\n";
            asm_output << "    syscall";
        }

        if (string_buffers_needed)
        {
            for (const std::any& buffer : string_buffers)
            {
                asm_output << std::any_cast<NodePrint>(buffer).contents.buffer_name << ":\n";
                asm_output << "    .asciz\"" << std::any_cast<NodePrint>(buffer).contents.string_literal.value.value() << "\"\n";
            }
        }


        return asm_output.str();
    }
}