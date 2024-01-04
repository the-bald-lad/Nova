#include "Lexer/Lexer.h"
#include "Parser/Parser.h"
#include "Asm_Generation/LinuxAsm.h"
#include "Errors/Errors.h"
#include "Timing/Timer.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#define NOVA_VERSION "0.0.2"
#define DEBUG

/**
 * @brief Get m_input from standard m_input and run the lexer on it.
 * This is the equivalent of running the command `nova` in a terminal.
*/
std::pair<std::string, std::string> std_input()
{
    std::string file_name = "stdin";

    std::string input;

    std::cout << "Nova Language Compiler v" << NOVA_VERSION << std::endl;

    std::cout << "Input >>> ";
    std::getline(std::cin, input);

    if (input == "exit")
        exit(0);

    return std::make_pair(input, file_name);
}

/**
 * @brief Get m_input from a file and run the lexer on it.
 * This is the equivalent of running the command `nova run <m_file_name>` in a terminal.
*/
std::pair<std::string, std::string> file_input(char* &file_name)
{
    // Get string from file

    std::string file_contents;

    std::stringstream contents_stream;
    std::fstream input(file_name, std::ios::in);
    contents_stream << input.rdbuf();
    file_contents = contents_stream.str();

    input.close();

    return std::make_pair(file_contents, file_name);
}

void make_asm(const std::vector<std::any>& root)
{
    if (root.empty())
    {
        std::cerr << "Root node has no value" << std::endl;  // Change this to custom error
        exit(1);
    }

    const Nova_Lang::Assembly_Generator asm_generator(root);

    // TODO: Fix working directory
    std::ofstream outfile {"../nova-build/out.asm" };
    outfile << asm_generator.generateAsm();

    outfile.close();
}

void output_debug_tokens(const std::vector<Nova_Lang::Token>& tokens)
{
    if (!Nova_Lang::error_buffer.empty())
    {
        for (const Nova_Lang::Base_Error& error : Nova_Lang::error_buffer)
            std::cout << error.As_String() << std::endl;
    }
    else // DEBUG: output m_tokens
    {
        bool first = true;
        for (const Nova_Lang::Token& token : tokens)
        {
            if (!first)
            {
                std::cout << " | " << token.Represent();
                continue;
            }

            std::cout << token.Represent();
            first = false;
        }
        std::cout << std::endl;
    }
}


int main(const int argc, char** argv)
{
    // Set up file information pair
    std::pair<std::string, std::string> file_info;

    // Check for file m_input, else use standard m_input
    if (argc == 1)
        file_info = std_input();
    else
        file_info = file_input(argv[1]);

    // Start compile timing
    Nova_Lang::Timer compile_timer;

    std::string file_contents = file_info.first;
    std::string file_name = file_info.second;

    auto tokens = Nova_Lang::run_lexer(file_contents, file_name);

#ifdef DEBUG
    std::cout << "Nova Language Compiler v" << NOVA_VERSION << std::endl;
    output_debug_tokens(tokens);
#endif // DEBUG

    Nova_Lang::Parser parser(std::move(tokens), file_name, 0);
    const std::vector<std::any> root = parser.Parse();

    make_asm(root);

    std::cout << "Build Finished in " << compile_timer.getDuration() << "ms" << std::endl;
}
