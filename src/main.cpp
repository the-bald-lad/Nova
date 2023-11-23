#include <iostream>
#include <string>

#include "Lexical_Analysis/Lexer.h"


void std_input()
{
    std::string file_name = "stdin";

    std::string input;

    std::cout << "Input > ";
    std::getline(std::cin, input);

    if (input == "exit")
        exit(0);

    std::vector<Nova_Lang::Token> tokens = Nova_Lang::run_lexer(input, file_name);

    for (Nova_Lang::Token token : tokens)
        std::cout << token.Represent() << " | ";
}

void file_input() {}  // TODO: Implement file input


int main()
{
    std_input();
}
