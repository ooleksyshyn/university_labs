#include <iostream>
#include <fstream>
#include <vector>

#include "KotlinLexer.hpp"

int main() {
    std::ifstream file("file.txt");

    KotlinLexer lexer;
    std::string line;
    std::vector<KotlinLexer::Token> tokens;

    while (std::getline(file, line)) {
        auto line_tokens = KotlinLexer::run(line);
    }

    return 0;
}
