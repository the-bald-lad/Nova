#pragma once

#include "Lexer/Token.h"
#include "Errors/Errors.h"

#include <vector>

namespace Nova_Lang
{
    struct NodeExpression
    {
        Token int_literal;
    };

    struct NodeExit
    {
        NodeExpression expression;
    };

    class Parser
    {
    public:
        explicit Parser(std::vector<Token> tokens, std::string file_name, int pos = 0);

        ~Parser();

        std::optional<NodeExpression> ParseExpression();

        std::optional<NodeExit> ParseExit();
    private:
        std::vector<Token> m_tokens;

        int m_parseIndex;

        std::string m_fileName;

        Token m_currentToken;
    private:
        std::optional<Token> NextNode(int offset = 1);

        Token PopNode();

        void AddError(std::string& error_name);
    };
}