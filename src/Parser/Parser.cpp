// TODO: Make recursive

#include "Parser.h"
#include "Errors/Errors.h"

#include <utility>

namespace Nova_Lang
{
    Parser::Parser(std::vector<Token> tokens, std::string file_name, int pos)
        : m_tokens(std::move(tokens)), m_fileName(std::move(file_name)), m_parseIndex(pos)
    {
    }

    Parser::~Parser() = default;

    // TODO: Add support for further expressions, such as `exit(1 + 9);`
    std::optional<NodeExpression> Parser::ParseExpression()
    {
        // No number was supplied to exit command, 1 is default code
        if (!NextNode().has_value() || NextNode().value().type != TokenTypes::T_INT_LITERAL)
        {
            // Remove left bracket
            PopNode();

            return NodeExpression{ .int_literal = Token({ .type = TokenTypes::T_INT_LITERAL, .value = "0" }) };
        }

        // Remove left bracket
        PopNode();

        // Check for right bracket
        if (!NextNode().has_value() || NextNode().value().type != TokenTypes::T_RBRACKET)
        {
            AddError((std::string &) "Missing bracket");
            return {};
        }

        return NodeExpression{ .int_literal = PopNode() };
    }

    std::optional<NodeExit> Parser::ParseExit()
    {
        // Exit node to be returned
        std::optional<NodeExit> exit;

        while (NextNode().has_value())
        {
            Token current_token = m_tokens.at(m_parseIndex);

            if (current_token.type == TokenTypes::T_EXIT)
            {
                // Check that next node is a left bracket
                if (!NextNode().has_value() || NextNode().value().type != TokenTypes::T_LBRACKET)
                {
                    AddError((std::string &) "Missing bracket");
                    break;
                }

                // Remove exit keyword
                PopNode();

                // Create exit node
                auto node_expression = ParseExpression();
                exit = NodeExit{ .expression = node_expression.value()};

                // Check if statement has been ended by a semicolon
                if (!NextNode().has_value() || NextNode().value().type != TokenTypes::T_SEMICOLON)
                {
                    AddError((std::string &) "Statement not ended by semicolon");
                }

                // Remove Right bracket
                PopNode();
            }
            else
            {
                // Removes token from vector
                PopNode();
            }
        }

        m_parseIndex = 0;

        return exit;
    }

    void Parser::AddError(std::string& error_name)
    {
        Parser_Error error = Parser_Error(m_currentToken, error_name, m_fileName);
        error_buffer.push_back(error);
    }

    std::optional<Token> Parser::NextNode(int offset)
    {
        if ((m_parseIndex + offset) >= m_tokens.size())
            return {};
        else
            return m_tokens.at(m_parseIndex + offset);
    }

    Token Parser::PopNode()
    {
        return m_tokens.at(m_parseIndex++);
    }
}