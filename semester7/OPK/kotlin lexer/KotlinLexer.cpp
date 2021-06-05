#include "KotlinLexer.hpp"

#include <array>

namespace {
    namespace lexer_utils {
        constexpr bool is_hard_key_word(const std::string_view text) {
            constexpr std::array hard_key_words = {
                    "as",
                    "as?",
                    "break",
                    "class",
                    "continue",
                    "do",
                    "else",
                    "false",
                    "for",
                    "fun",
                    "if",
                    "in",
                    "interface",
                    "is",
                    "!is",
                    "object",
                    "package",
                    "return",
                    "super",
                    "this",
                    "throw",
                    "true",
                    "try",
                    "typealias",
                    "typeof",
                    "val",
                    "var",
                    "when",
                    "while",
            };

            const auto it = std::find(hard_key_words.begin(), hard_key_words.end(), text);
            return it != hard_key_words.end();
        }

        constexpr bool is_soft_key_word(const std::string_view text) {
            constexpr std::array soft_key_words = {
                    "by",
                    "catch",
                    "constructor",
                    "delegate",
                    "dynamic",
                    "field",
                    "file",
                    "finally",
                    "get",
                    "import",
                    "init",
                    "param",
                    "property",
                    "receiver",
                    "set",
                    "setparam",
                    "value",
                    "where",

                    "it",

                    "actual",
                    "abstract",
                    "annotation",
                    "companion",
                    "const",
                    "crossinline",
                    "data",
                    "enum",
                    "expect",
                    "external",
                    "final",
                    "infix",
                    "inline",
                    "inner",
                    "internal",
                    "lateinit",
                    "noinline",
                    "open",
                    "operator",
                    "out",
                    "override",
                    "private",
                    "protected",
                    "public",
                    "reified",
                    "sealed",
                    "suspend",
                    "tailrec",
                    "vararg",
            };

            const auto it = std::find(soft_key_words.begin(), soft_key_words.end(), text);
            return it != soft_key_words.end();
        }
    }
}


class KotlinLexer::Impl {
    enum class State {
        EMPTY,
    };

    std::vector<Token> tokens;
    std::string current_token;
    State state = State::EMPTY;
public:
    std::vector<Token> operator() (const std::string_view line) {
        tokens.clear();
        current_token.clear();
        state = State::EMPTY;

        for (const auto ch : line) {
            if (std::isspace(ch)) {
            }
        }

        return std::move(tokens);
    }
};


KotlinLexer::Token::Token(std::string&& text, Type type) noexcept : text{std::move(text)}, type{type} {}


auto KotlinLexer::run(const std::string_view line) -> std::vector<Token> {
    KotlinLexer::Impl impl;
    return impl(line);
}
