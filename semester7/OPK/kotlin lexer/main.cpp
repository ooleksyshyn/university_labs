#include <iostream>
#include <fstream>
#include <filesystem>

#include "KotlinLexer.hpp"

int main() {
    const auto path = std::filesystem::current_path().parent_path() / "code_sample.txt";

    std::ifstream file(path);
    const std::string code{std::istreambuf_iterator<char>(file),std::istreambuf_iterator<char>()};

    std::cout << "Code:\n" << code << std::endl;
    const auto tokens = KotlinLexer::run(code);

    std::cout << "\nTokens:\n";

    for (const auto& [text, type] : tokens) {
        std::cout << "Token " << tokenName(type) << " : " << text << std::endl;
    }

    return 0;
}
