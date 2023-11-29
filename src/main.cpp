#include "Lexical_Analysis/Lexer.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#define NOVA_VERSION "0.0.1"
#define DEBUG

/**
 * @brief Get input from standard input and run the lexer on it.
 * This is the equivalent of running the command `nova run` in a terminal.
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


int main(int argc, char** argv)
{
    std::pair<std::string, std::string> file_info;
    // Check for file input, else use standard input
    if (argc == 1)
        file_info = std_input();
    else
        file_info = file_input(argv[1]);

    auto lexer_pair = Nova_Lang::run_lexer(file_info.first, file_info.second);

    std::vector<Nova_Lang::Token> tokens = lexer_pair.first;

    std::vector<Nova_Lang::Base_Error> errors = lexer_pair.second;

#ifdef DEBUG
    std::cout << "Nova Language Compiler v" << NOVA_VERSION << std::endl;
    if (!errors.empty())
    {
        for (const Nova_Lang::Base_Error& error : errors)
            std::cout << error.As_String() << std::endl;
    }
    else // Temporary: output tokens
    {
        for (const Nova_Lang::Token& token : tokens)
            std::cout << token.Represent() << " | ";
        std::cout << std::endl;
    }
#endif

    std::cout << "Build Finished" << std::endl;
}
