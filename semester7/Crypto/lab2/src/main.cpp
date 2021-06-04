#include <iostream>

#include "RC6.hpp"

int main() {

    const std::string userkey = "0123456789abcdef0112233445566778899aabbccddeeff0";
    const std::string text = "abcdefghijklmnop";

    std::cout << "text:      " << text << std::endl;

    RC6 rc6(32, 20, userkey.size() / 2);
    std::string result = rc6.run(RC6::Encrypt, text, userkey);

    std::cout << "encrypted: " << result << std::endl;

    std::string source = rc6.run(RC6::Decrypt, result, userkey);

    std::cout << "decrypted: " << source << std::endl;

    return 0;
}
