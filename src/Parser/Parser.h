#pragma once

#include "Lexer/Token.h"
#include "Errors/Errors.h"

#include <vector>
#include <any>

namespace Nova_Lang
{
    struct NodeIntExpression
    {
        Token int_literal;
    };

    struct NodeContents
    {
        Token string_literal;

        // Token meta info
        uint32_t length = 0;
        std::string buffer_name;
    };

    struct NodeExit
    {
        NodeIntExpression expression;
    };

    struct NodePrint
    {
        NodeContents contents;
    };



    class Parser
    {
    public:
        explicit Parser(std::vector<Token> tokens, std::string file_name, int pos = 0);

        ~Parser();

        std::optional<NodeIntExpression> ParseIntExpression();
        std::optional<NodeContents> ParseStringExpression();

        std::vector<std::any> Parse();
    private: // Attributes
        std::vector<Token> m_tokens;

        std::string m_fileName;

        int m_parseIndex;

        Token m_currentToken;
    private: // Methods
        std::optional<Token> NextNode(int offset = 1);

        Token PopNode();

        void AddError(const std::string& error_name) const;

        [[nodiscard]] bool LeftBracketPresent();
        [[nodiscard]] bool RightBracketPresent();
        [[nodiscard]] bool SemicolonPresent();
    };
}