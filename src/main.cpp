#include <iostream>
#include <string>

#include "Lexical_Analysis/Lexer.h"

/**
 * @brief Get input from standard input and run the lexer on it.
 * This is the equivalent of running the command `nova run` in a terminal.
*/
void std_input()
{
    std::string file_name = "stdin";

    std::string input;

    std::cout << "Input > ";
    std::getline(std::cin, input);

    if (input == "exit")
        exit(0);

    auto lexer_pair = Nova_Lang::run_lexer(input, file_name);

    std::vector<Nova_Lang::Token> tokens = lexer_pair.first;

    std::vector<Nova_Lang::Base_Error> errors = lexer_pair.second;

    if (!errors.empty())
    {
        for (const Nova_Lang::Base_Error& error : errors)
            std::cout << error.As_String() << std::endl;
    }
    else // Temporary: output tokens
    {
        for (const Nova_Lang::Token& token : tokens)
            std::cout << token.Represent() << " | ";
    }
}

// TODO: Implement file input
void file_input()
{
    // Get string from file


}


int main()
{
    std_input();
}
