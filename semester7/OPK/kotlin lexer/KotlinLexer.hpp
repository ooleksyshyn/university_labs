#ifndef KOTLIN_LEXER_KOTLINLEXER_HPP
#define KOTLIN_LEXER_KOTLINLEXER_HPP

#include <vector>
#include <string_view>
#include <string>


class KotlinLexer {
public:
    /// @todo string literals
    /// @todo char literals
    /// @todo underscores in numeric literals
    struct Token {
        enum class Type {
            HARD_KEYWORD,
            SOFT_KEYWORD,
            WORD,
            COMMENT,
            ARITHMETICAL_OPERATOR, // arithmetical operator (incl. logical, excl. '*')
            OPERATOR, // non-arithmetical operators and punctuation marks
            STAR, // '*' -- can be used as operator and array unpacking
            LITERAL,
            STRING_LITERAL, // string and char
            ERROR,
        };

        Token(std::string&& text, Type type) noexcept;

        const std::string text;
        const Type type;
    };

    [[nodiscard]] static std::vector<Token> run(std::string_view line);
};


#endif //KOTLIN_LEXER_KOTLINLEXER_HPP
