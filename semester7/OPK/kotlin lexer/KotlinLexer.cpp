#include "KotlinLexer.hpp"

#include <array>
#include <unordered_map>
#include <functional>
#include <iostream>

namespace {

    template<typename Container, typename T>
    constexpr bool contains(const Container& cont, const T& val) {
        const auto it = std::find(cont.begin(), cont.end(), val);
        return it != cont.end();
    }

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
            return contains(hard_key_words, text);
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
            return contains(soft_key_words, text);
        }

        constexpr bool is_punctuation(const char ch) {
            constexpr std::array punctuation = {
                    '{', '}', '[', ']', '(', ')',
                    ',', ';', '@'
            };
            return contains(punctuation, ch);
        }

        constexpr bool is_simple_combined_operator_start(const char ch) {
            constexpr std::array symbols = {
                    '%', '>', '<'
            };
            return contains(symbols, ch);
        }

        constexpr bool is_special_slash_symbol(const char ch) {
            constexpr std::array symbols = {
                    't', 'b', 'n', 'r', '\'', '"',
                    '\\', '$',
            };

            return contains(symbols, ch);
        }

        constexpr bool is_hex_digit(const char ch) {
            constexpr std::array hex_letters = {
                    'a', 'b', 'c', 'd', 'e', 'f'
            };

            return std::isdigit(ch) || contains(hex_letters, std::tolower(ch));
        }


        class KotlinLexerImpl {
            enum class State {
                EMPTY,
                TEXT,
                COMMENT,
                MULTI_LINE_COMMENT,
                POINT,
                PLUS,
                MINUS,
                STAR,
                SLASH,
                EQUAL,
                NOT,
                COMBINED_OPERATOR_START,
                AMPERSAND,
                DOUBLE_DOT,
                QUESTION_MARK,
                INTEGER_LITERAL,
                ZERO,
                UNDERSCORE,
                CHAR_LITERAL,
                STRING_LITERAL,

                FLOAT_LITERAL,
                SPECIAL_SYMBOL_IN_CHAR_LITERAL,
                UNICODE_CHAR_LITERAL,
                BINARY_LITERAL,
                HEX_LITERAL,

                ERROR,
            };

            using This = KotlinLexerImpl;
            using Token = KotlinLexer::Token;
            using Type = Token::Type;
            using Handler = void(This::*)(const char);

            std::vector<Token> tokens;
            std::string current_token;
            State state = State::EMPTY;

            void handle(const char ch) {
                static const std::unordered_map<State, Handler> handlers = {
                        {State::EMPTY, &This::handleEmpty},
                        {State::TEXT, &This::handleText},
                        {State::COMMENT, &This::handleComment},
                        {State::MULTI_LINE_COMMENT, &This::handleMultiLineComment},
                        {State::POINT, &This::handlePoint},
                        {State::PLUS, &This::handlePlus},
                        {State::MINUS, &This::handleMinus},
                        {State::STAR, &This::handleStar},
                        {State::SLASH, &This::handleSlash},
                        {State::EQUAL, &This::handleEqual},
                        {State::NOT, &This::handleNot},
                        {State::COMBINED_OPERATOR_START, &This::handleCombinedOperator},
                        {State::AMPERSAND, &This::handleAmpersand},
                        {State::DOUBLE_DOT, &This::handleDoubleDot},
                        {State::QUESTION_MARK, &This::handleQuestionMark},
                        {State::INTEGER_LITERAL, &This::handleIntegerLiteral},
                        {State::ZERO, &This::handleZero},
                        {State::UNDERSCORE, &This::handleUnderscore},
                        {State::STRING_LITERAL, &This::handleStringLiteral},
                        {State::CHAR_LITERAL, &This::handleCharLiteral},

                        {State::FLOAT_LITERAL, &This::handleFloatLiteral},
                        {State::SPECIAL_SYMBOL_IN_CHAR_LITERAL, &This::handleSpecialChar},
                        {State::UNICODE_CHAR_LITERAL, &This::handleUnicodeChar},
                        {State::BINARY_LITERAL, &This::handleBinaryLiteral},
                        {State::HEX_LITERAL, &This::handleHexLiteral},

                        {State::ERROR, &This::handleError},
                };

                if (const auto handlerIt = handlers.find(state); handlerIt != handlers.end()) {
                    ((*this).*(handlerIt->second))(ch);
                } else {
                    throw std::logic_error("[KotlinLexerImpl::handle] this state is not handled: "
                                                    + std::to_string(static_cast<int>(state)));
                }
            }

            void push_token(const Type type) {
                tokens.emplace_back(std::move(current_token), type);
                state = State::EMPTY;
            }

            void handleEmpty(const char ch) {
                if (ch == '+') {
                    state = State::PLUS;
                    current_token.push_back(ch);
                } else if (ch == '-') {
                    state = State::MINUS;
                    current_token.push_back(ch);
                } else if (ch == '*') {
                    state = State::STAR;
                    current_token.push_back(ch);
                } else if (ch == '/') {
                    state = State::SLASH;
                    current_token.push_back(ch);
                } else if (ch == '.') {
                    state = State::POINT;
                    current_token.push_back(ch);
                } else if (is_simple_combined_operator_start(ch)) {
                    state = State::COMBINED_OPERATOR_START;
                    current_token.push_back(ch);
                } else if (is_punctuation(ch)) {
                    current_token = ch;
                    push_token(Type::OPERATOR);
                } else if (ch == '0') {
                    state = State::ZERO;
                    current_token.push_back(ch);
                } else if (std::isdigit(ch)) {
                    state = State::INTEGER_LITERAL;
                    current_token.push_back(ch);
                } else if (ch == '!') {
                    state = State::NOT;
                    current_token.push_back(ch);
                } else if (ch == '=') {
                    state = State::EQUAL;
                    current_token.push_back(ch);
                } else if (ch == '&') {
                    state = State::AMPERSAND;
                    current_token.push_back(ch);
                } else if (ch == ':') {
                    state = State::DOUBLE_DOT;
                    current_token.push_back(ch);
                } else if (ch == '?') {
                    state = State::QUESTION_MARK;
                    current_token.push_back(ch);
                } else if (std::isspace(ch)) {
                    return;
                } else if (std::isalpha(ch)) {
                    state = State::TEXT;
                    current_token.push_back(ch);
                } else if (ch == '_') {
                    state = State::UNDERSCORE;
                    current_token.push_back(ch);
                } else if (ch == '\'') {
                    state = State::CHAR_LITERAL;
                    current_token.push_back(ch);
                } else if (ch == '"') {
                    state = State::STRING_LITERAL;
                    current_token.push_back(ch);
                } else {
                    state = State::ERROR;
                    handleError(ch);
                }
            }

            void handleText(const char ch) {
                if (std::isalnum(ch) || ch == '_') {
                    current_token.push_back(ch);
                } else {
                    state = State::EMPTY;

                    if (is_hard_key_word(current_token)) {
                        push_token(Type::HARD_KEYWORD);
                    } else if (is_soft_key_word(current_token)) {
                        push_token(Type::SOFT_KEYWORD);
                    } else {
                        push_token(Type::IDENTIFIER);
                    }

                    handleEmpty(ch);
                }
            }

            void handleComment(const char ch) {
                if (ch == '\n') {
                    push_token(Type::COMMENT);
                    state = State::EMPTY;
                } else {
                    current_token.push_back(ch);
                }
            }

            void handleMultiLineComment(const char ch) {
                if (ch == '/' && current_token.back() == '*') {
                    state = State::EMPTY;
                    current_token.push_back(ch);
                    push_token(Type::COMMENT);
                } else {
                    current_token.push_back(ch);
                }
            }

            void handlePoint(const char ch) {
                state = State::EMPTY;
                if (ch == '.') {
                    current_token.push_back(ch);
                    push_token(Type::OPERATOR);
                } else {
                    push_token(Type::OPERATOR);
                    handleEmpty(ch);
                }
            }

            void handlePlus(const char ch) {
                state = State::EMPTY;
                if (ch == '=' || ch == '+') {
                    current_token.push_back(ch);
                    push_token(Type::ARITHMETICAL_OPERATOR);
                } else {
                    push_token(Type::ARITHMETICAL_OPERATOR);
                    handleEmpty(ch);
                }
            }

            void handleCombinedOperator(const char ch) {
                state = State::EMPTY;
                if (ch == '=') {
                    current_token.push_back(ch);
                    push_token(Type::ARITHMETICAL_OPERATOR);
                } else {
                    push_token(Type::ARITHMETICAL_OPERATOR);
                    handleEmpty(ch);
                }
            }

            void handleSlash(const char ch) {
                if (ch == '*') {
                    state = State::MULTI_LINE_COMMENT;
                    current_token.push_back(ch);
                } else if (ch == '/') {
                    state = State::COMMENT;
                    current_token.push_back(ch);
                } else if (ch == '=') {
                    state = State::EMPTY;
                    current_token.push_back(ch);
                    push_token(Type::ARITHMETICAL_OPERATOR);
                } else {
                    state = State::EMPTY;
                    push_token(Type::ARITHMETICAL_OPERATOR);
                    handleEmpty(ch);
                }
            }

            void handleMinus(const char ch) {
                if (ch == '>' || ch == '-' || ch == '=') {
                    current_token.push_back(ch);
                    state = State::EMPTY;
                    push_token(Type::OPERATOR);
                } else {
                    push_token(Type::OPERATOR);
                    state = State::EMPTY;
                    handleEmpty(ch);
                }
            }

            void handleStar(const char ch) {
                state = State::EMPTY;
                if (ch == '=') {
                    current_token.push_back(ch);
                    push_token(Type::ARITHMETICAL_OPERATOR);
                } else {
                    push_token(Type::OPERATOR);
                    handleEmpty(ch);
                }
            }

            void handleEqual(const char ch) {
                if (current_token == "==" && ch == '=') {
                    current_token.push_back(ch);
                    state = State::EMPTY;
                    push_token(Type::OPERATOR);
                } else if (ch == '=') {
                    current_token.push_back(ch);
                } else {
                    state = State::EMPTY;
                    push_token(Type::OPERATOR);
                    handleEmpty(ch);
                }
            }

            void handleNot(const char ch) {
                if (current_token == "!=" && ch == '=') {
                    state = State::EMPTY;
                    current_token.push_back(ch);
                    push_token(Type::OPERATOR);
                } else if (ch == '=') {
                    current_token.push_back(ch);
                } else if (ch == '!') {
                    current_token.push_back(ch);
                    push_token(Type::OPERATOR);
                    state = State::EMPTY;
                } else {
                    state = State::EMPTY;
                    push_token(Type::OPERATOR);
                    handleEmpty(ch);
                }
            }

            void handleAmpersand(const char ch) {
                if (ch == '&') {
                    current_token.push_back(ch);
                    push_token(Type::OPERATOR);
                    state = State::EMPTY;
                } else {
                    state = State::ERROR;
                    handleError(ch);
                }
            }

            void handleDoubleDot(const char ch) {
                state = State::EMPTY;
                if (ch == ':') {
                    current_token.push_back(ch);
                    push_token(Type::OPERATOR);
                } else {
                    push_token(Type::OPERATOR);
                    handleEmpty(ch);
                }
            }

            void handleQuestionMark(const char ch) {
                state = State::EMPTY;
                if (ch == '.' || ch == ':') {
                    current_token.push_back(ch);
                    push_token(Type::OPERATOR);
                } else {
                    push_token(Type::OPERATOR);
                    handleEmpty(ch);
                }
            }

            void handleIntegerLiteral(const char ch) {
                if (std::isdigit(ch)) {
                    current_token.push_back(ch);
                } else if (ch == '.' && current_token.back() == '_') {
                    state = State::ERROR;
                    handleError(ch);
                } else if (ch == '.') {
                    current_token.push_back(ch);
                    state = State::FLOAT_LITERAL;
                } else if (ch == '_') {
                    current_token.push_back(ch);
                } else if (current_token.back() == '_') {
                    state = State::ERROR;
                    handleError(ch);
                } else if (ch == 'L' || std::tolower(ch) == 'u') {
                    current_token.push_back(ch);
                    state = State::EMPTY;
                    push_token(Type::LITERAL);
                } else {
                    state = State::EMPTY;
                    push_token(Type::LITERAL);
                    handleEmpty(ch);
                }
            }

            void handleZero(const char ch) {
                if (std::tolower(ch) == 'x') {
                    state = State::HEX_LITERAL;
                    current_token.push_back(ch);
                } if (std::tolower(ch) == 'b') {
                    state = State::BINARY_LITERAL;
                    current_token.push_back(ch);
                } else if (std::isdigit(ch) || ch == '.') {
                    state = State::FLOAT_LITERAL;
                    current_token.push_back(ch);
                } else {
                    state = State::EMPTY;
                    push_token(Type::LITERAL);
                    handleEmpty(ch);
                }
            }

            void handleUnderscore(const char ch) {
                if (std::isalpha(ch)) {
                    state = State::TEXT;
                    current_token.push_back(ch);
                } else {
                    state = State::EMPTY;
                    push_token(Type::OPERATOR);
                    handleEmpty(ch);
                }
            }

            void handleStringLiteral(const char ch) {
                if (ch == '\n') {
                    state = State::ERROR;
                    handleError(ch);
                } else if (ch == '"') {
                    auto i = current_token.size() - 1;
                    std::size_t n_slashes = 0;
                    while (current_token[i] == '\\') {
                        --i;
                        ++n_slashes;
                    }
                    if (n_slashes % 2 == 0) {
                        state = State::EMPTY;
                        current_token.push_back(ch);
                        push_token(Type::STRING_LITERAL);
                    } else {
                        current_token.push_back(ch);
                    }
                } else {
                    current_token.push_back(ch);
                }
            }

            void handleCharLiteral(const char ch) {
                if (ch == '\\' && current_token.size() == 1) {
                    current_token.push_back(ch);
                    state = State::SPECIAL_SYMBOL_IN_CHAR_LITERAL;
                } else if (current_token.size() == 1) {
                    current_token.push_back(ch);
                } else if (current_token.size() == 2 && ch == '\'') {
                    state = State::EMPTY;
                    current_token.push_back(ch);
                    push_token(Type::STRING_LITERAL);
                } else {
                    state = State::ERROR;
                    handleError(ch);
                }
            }

            void handleFloatLiteral(const char ch) {
                const bool hasPoint = contains(current_token, '.');

                if (std::isdigit(ch) || (!hasPoint && ch == '_')) {
                    current_token.push_back(ch);
                } else if (!hasPoint && ch == '.') {
                    if (current_token.back() == '_') {
                        state = State::ERROR;
                        handleError(ch);
                    } else {
                        current_token.push_back(ch);
                    }
                } else if (ch == '.' && current_token.back() == '.') {
                    if (current_token.front() != '0') {
                        // integer literal and range operator
                        current_token.pop_back();
                        push_token(Type::LITERAL);
                        current_token = "..";
                        push_token(Type::OPERATOR);
                        state = State::EMPTY;
                    } else {
                        state = State::ERROR;
                        handleError(ch);
                    }
                } else if (hasPoint && ch == '.') {
                    // operator . on float
                    state = State::EMPTY;
                    push_token(Type::LITERAL);
                    handleEmpty(ch);
                } else if (std::tolower(ch) == 'f' && current_token.back() != '.') {
                    current_token.push_back(ch);
                    state = State::EMPTY;
                    push_token(Type::LITERAL);
                } else if (current_token.back() == '.') {
                    // float literal with dot as last character
                    state = State::ERROR;
                    handleError(ch);
                } else {
                    state = State::EMPTY;
                    push_token(Type::LITERAL);
                    handleEmpty(ch);
                }
            }

            void handleSpecialChar(const char ch) {
                if (current_token.size() == 2 && ch == 'u') {
                    state = State::UNICODE_CHAR_LITERAL;
                    current_token.push_back(ch);
                } else if (current_token.size() == 2 && is_special_slash_symbol(ch)) {
                    current_token.push_back(ch);
                } else if (current_token.size() == 3 && ch == '\'') {
                    current_token.push_back(ch);
                    push_token(Type::STRING_LITERAL);
                    state = State::EMPTY;
                } else {
                    state = State::ERROR;
                    handleError(ch);
                }
            }

            void handleUnicodeChar(const char ch) {
                if (current_token.size() < 7 && is_hex_digit(ch)) {
                    current_token.push_back(ch);
                } else if (current_token.size() == 7 && ch == '\'') {
                    current_token.push_back(ch);
                    push_token(Type::STRING_LITERAL);
                    state = State::EMPTY;
                } else {
                    state = State::ERROR;
                    handleError(ch);
                }
            }

            void handleBinaryLiteral(const char ch) {
                if (ch == '0' || ch == '1') {
                    current_token.push_back(ch);
                } else if (ch == '_' && std::tolower(current_token.back()) == 'b') {
                    state = State::ERROR;
                    handleError(ch);
                } else if (ch == '_') {
                    current_token.push_back(ch);
                } else {
                    state = State::EMPTY;
                    push_token(Type::LITERAL);
                    handleEmpty(ch);
                }
            }


            void handleHexLiteral(const char ch) {
                if (is_hex_digit(ch)) {
                    current_token.push_back(ch);
                } else if (ch == '_' && std::tolower(current_token.back()) == 'x') {
                    state = State::ERROR;
                    handleError(ch);
                } else if (ch == '_') {
                    current_token.push_back(ch);
                } else {
                    state = State::EMPTY;
                    push_token(Type::LITERAL);
                    handleEmpty(ch);
                }
            }


            void handleError(const char ch) {
                state = State::EMPTY;
                current_token.push_back(ch);
                push_token(Type::ERROR);
            }

            void finish() {
                if (state == State::MULTI_LINE_COMMENT) {
                    state = State::ERROR;
                    handleError('\n');
                } else {
                    handle('\n');
                }
            }

        public:
            std::vector<Token> operator() (const std::string& code) {
                tokens.clear();
                current_token.clear();
                state = State::EMPTY;

                for (const auto ch : code) {
                    handle(ch);
                }

                finish();

                return std::move(tokens);
            }
        };
    }
}


KotlinLexer::Token::Token(std::string&& text, Type type) noexcept : text{std::move(text)}, type{type} {}


auto KotlinLexer::run(const std::string& code) -> std::vector<Token> {
    lexer_utils::KotlinLexerImpl impl;
    return impl(code);
}
