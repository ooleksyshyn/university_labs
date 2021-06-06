#ifndef KOTLIN_LEXER_KOTLINLEXER_HPP
#define KOTLIN_LEXER_KOTLINLEXER_HPP

#include <vector>
#include <string_view>
#include <string>


class KotlinLexer {
public:
    struct Token {
        enum class Type {
            HARD_KEYWORD,
            SOFT_KEYWORD,
            IDENTIFIER,
            COMMENT,
            ARITHMETICAL_OPERATOR, // arithmetical operator (incl. logical, excl. '*')
            OPERATOR, // non-arithmetical operators and punctuation marks
            LITERAL,
            STRING_LITERAL, // string and char
            ERROR,
        };

        Token(std::string&& text, Type type) noexcept;

        const std::string text;
        const Type type;
    };

    [[nodiscard]] static std::vector<Token> run(const std::string& code);
};


constexpr std::string_view tokenName(KotlinLexer::Token::Type type) {
    using Type = KotlinLexer::Token::Type;
    switch (type) {
        case Type::HARD_KEYWORD:
            return "hard keyword";
        case Type::SOFT_KEYWORD:
            return "soft keyword";
        case Type::IDENTIFIER:
            return "identifier";
        case Type::COMMENT:
            return "comment";
        case Type::ARITHMETICAL_OPERATOR:
            return "arithmetical operator";
        case Type::OPERATOR:
            return "operator";
        case Type::LITERAL:
            return "literal";
        case Type::STRING_LITERAL:
            return "string literal";
        case Type::ERROR:
            return "error";
    }
}


#endif //KOTLIN_LEXER_KOTLINLEXER_HPP
