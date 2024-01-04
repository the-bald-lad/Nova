#include "Parser.h"
#include "Errors/Errors.h"

#include <utility>

namespace Nova_Lang
{
    Parser::Parser(std::vector<Token> tokens, std::string file_name, const int pos)
        : m_tokens(std::move(tokens)), m_fileName(std::move(file_name)), m_parseIndex(pos)
    {
    }

    Parser::~Parser() = default;

    // TODO: Add support for further expressions, such as `exit(1 + 9);`
    std::optional<NodeIntExpression> Parser::ParseIntExpression()
    {
        // No number was supplied to exit command, 1 is default code
        if (!NextNode().has_value() || NextNode().value().type != TokenTypes::T_INT_LITERAL)
        {
            // Remove left bracket
            PopNode();

            return NodeIntExpression{ .int_literal = Token({ .type = TokenTypes::T_INT_LITERAL, .value = "0" }) };
        }

        // Remove left bracket
        PopNode();

        // Check for right bracket
        if (!NextNode().has_value() || NextNode().value().type != TokenTypes::T_RBRACKET)
        {
            AddError((std::string &) "Missing bracket");
            return {};
        }

        return NodeIntExpression{ .int_literal = PopNode() };
    }

    std::optional<NodeContents> Parser::ParseStringExpression()
    {
        NodeContents output{ .string_literal = PopNode() };

        const std::optional node_string = output.string_literal.value;
        const size_t string_literal_length = node_string->length();

        output.length = string_literal_length + 1;

        // TODO: THIS IS VERY TEMPORARY!!!!
        output.buffer_name = output.string_literal.value.value_or("beans");

        return output;
    }

    bool Parser::LeftBracketPresent()
    {
        if (!NextNode().has_value() || NextNode().value().type != TokenTypes::T_LBRACKET)
        {
            AddError("Missing Left Bracket");
            return false;
        }

        // Left bracket is present
        return true;
    }

    bool Parser::RightBracketPresent()
    {
        if (!NextNode().has_value() || NextNode().value().type != TokenTypes::T_RBRACKET)
        {
            AddError("Missing Right Bracket");
            return false;
        }

        // Right bracket is present
        return true;
    }

    bool Parser::SemicolonPresent()
    {
        if (!NextNode().has_value() || NextNode().value().type != TokenTypes::T_SEMICOLON)
        {
            AddError("Statement Not Ended By Semicolon");
            return false;
        }

        // Semicolon is present
        return true;
    }


    // Parse from tokens
    std::vector<std::any> Parser::Parse()
    {
        // TODO: No values are placed into vector
        // To be returned at the end of parse
        std::vector<std::any> ast;

        while (NextNode().has_value())
        {
            const auto [type, value] = m_tokens.at(m_parseIndex);

            if (type == TokenTypes::T_EXIT)
            {
                // Check for left bracket
                if (!LeftBracketPresent())
                {
                    break;
                }

                // Remove exit keyword
                PopNode();

                // Create exit node
                std::optional<NodeIntExpression> node_expression = ParseIntExpression();

                std::optional exit = NodeExit{ .expression = node_expression.value() };

                // Check if statement has been ended by a semicolon
                if (!SemicolonPresent())
                {
                    break;
                }

                // Remove Right bracket
                PopNode();

                // Add exit node to return tree
                ast.emplace_back(exit);
            }
            else if (type == TokenTypes::T_PRINT)
            {
                // Check for left bracket
                if (!LeftBracketPresent())
                {
                    break;
                }

                // Remove left bracket
                PopNode();

                // Create print node
                auto node_contents = ParseStringExpression();

                auto print = NodePrint{ .contents = node_contents.value() };

                // Check for semicolon
                if (!SemicolonPresent())
                {
                    break;
                }

                // Remove right bracket
                PopNode();

                // Add print node to the tree
                ast.emplace_back(print);
            }
            else
            {
                // Removes token from vector
                PopNode();
            }
        }

        m_parseIndex = 0;

        return ast;
    }

    void Parser::AddError(const std::string& error_name) const
    {
        const auto error = Parser_Error(m_currentToken, error_name, m_fileName);
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