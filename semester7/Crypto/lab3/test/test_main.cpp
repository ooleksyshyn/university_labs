#include "catch.hpp"
#include "../src/hash.hpp"

TEST_CASE("Hash", "[Hash]") {

    SECTION("some text from wiki") {
        const char* filename = "test1.txt";
        const auto hash = ripemd160(filename);

        REQUIRE(hash == "37f332f68db77bd9d7edd4969571ad671cf9dd3b");
        REQUIRE(hash == ripemd160(filename));
        REQUIRE(hash.size() == 40);
    }

    SECTION("some text from wiki with little change") {
        const char* filename = "test2.txt";
        const auto hash = ripemd160(filename);

        REQUIRE(hash == "132072df690933835eb8b6adb77e7b6f14acad7");
        REQUIRE(hash == ripemd160(filename));
    }

    SECTION("empty text") {
        const char* filename = "test3.txt";
        const auto hash = ripemd160(filename);

        REQUIRE(hash == "9c1185a5c5e9fc54612808977ee8f548b2258d31");
        REQUIRE(hash == ripemd160(filename));
        REQUIRE(hash.size() == 40);
    }

}