#include "../src/RC6.hpp"
#include "catch.hpp"

TEST_CASE("Test RC6/32/*/*", "[RC6_32]") {

    SECTION("Simple encoding") {
        const std::string key = "8136790daf245789";
        RC6 rc6(32, 20, key.size() / 2);

        std::string text = "qbajfn;vvszbk fd";
        auto encrypted = rc6.run(RC6::Encrypt, text, key);
        auto decrypted = rc6.run(RC6::Decrypt, encrypted, key);

        REQUIRE(text == decrypted);
        REQUIRE(encrypted == "cb4169012fac15d29af52a2efe7746fc");

        text = "iwantnobreakfree";
        encrypted = rc6.run(RC6::Encrypt, text, key);
        decrypted = rc6.run(RC6::Decrypt, encrypted, key);

        REQUIRE(text == decrypted);
        REQUIRE(encrypted == "c27aa7546e9778633c75bffca94cbe4e");
    }

    SECTION("With another key") {
        const std::string key = "c8136790daf24578957389";
        RC6 rc6(32, 20, key.size() / 2);

        std::string text = "to say I love yo";
        auto encrypted = rc6.run(RC6::Encrypt, text, key);
        auto decrypted = rc6.run(RC6::Decrypt, encrypted, key);

        REQUIRE(text == decrypted);
        REQUIRE(encrypted == "ce65bf759dad8bd3aad1f81194c302a0");
    }


    SECTION("More rounds") {
        const std::string key = "c8136790daf24578957389";
        RC6 rc6(32, 30, key.size() / 2);

        std::string text = "to say I love yo";
        auto encrypted = rc6.run(RC6::Encrypt, text, key);
        auto decrypted = rc6.run(RC6::Decrypt, encrypted, key);

        REQUIRE(text == decrypted);
        REQUIRE(encrypted == "5631e6c10ad2b299eed3c5525d1d6334");

        text = "iwantnobreakfree";
        encrypted = rc6.run(RC6::Encrypt, text, key);
        decrypted = rc6.run(RC6::Decrypt, encrypted, key);

        REQUIRE(text == decrypted);
        REQUIRE(encrypted == "3cf4c3186b8a054fe3c563a88cb51c69");
    }
}
