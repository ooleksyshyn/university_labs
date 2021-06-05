#include "KotlinLexer.hpp"

#include <array>
#include <unordered_map>
#include <functional>

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
                    ',', ';', '@', '_'
            };
            return contains(punctuation, ch);
        }

        constexpr bool is_simple_combined_operator_start(const char ch) {
            constexpr std::array symbols = {
                    '%', '>', '<'
            };
            return contains(symbols, ch);
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
                        {State::TEXT, &This::handleEmpty},
                        {State::COMMENT, &This::handleComment},
                        {State::MULTI_LINE_COMMENT, &This::handleMultiLineComment},
                        {State::POINT, &This::handlePoint},
                        {State::PLUS, &This::handlePlus},
                        {State::COMBINED_OPERATOR_START, &This::handleCombinedOperator},
                        {State::SLASH, &This::handleSlash},
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
                    // ???
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
                } else {
                    state = State::ERROR;
                }
            }

            void handleText(const char ch);
            void handleComment(const char ch);
            void handleMultiLineComment(const char ch);
            void handlePoint(const char ch);
            void handlePlus(const char ch);
            void handleCombinedOperator(const char ch);
            void handleSlash(const char ch);
        public:
            std::vector<Token> operator() (const std::string_view line) {
                tokens.clear();
                current_token.clear();
                state = State::EMPTY;

                for (const auto ch : line) {
                    handle(ch);
                }

                return std::move(tokens);
            }
        };
    }
}


KotlinLexer::Token::Token(std::string&& text, Type type) noexcept : text{std::move(text)}, type{type} {}


auto KotlinLexer::run(const std::string_view line) -> std::vector<Token> {
    lexer_utils::KotlinLexerImpl impl;
    return impl(line);
}
