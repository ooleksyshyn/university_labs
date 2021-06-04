#include <iostream>

#include "hash.hpp"

int main() {
    std::cout << "The quick brown fox jumps over the lazy dog\n" << "Hash: " << ripemd160("file.txt");
    return 0;
}
