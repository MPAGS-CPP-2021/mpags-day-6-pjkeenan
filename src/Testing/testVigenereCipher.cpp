//! Unit Tests for MPAGSCipher CaesarCipher Class
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "VigenereCipher.hpp"

// Needs to use a lambda for the constructor to use it in REQUIRE_THROWS_AS and REQUIRE_NOTHROW
auto constructVigenereCipher = [](const std::string& key) {
    VigenereCipher vc{key};
};

TEST_CASE("Vigenere Cipher encryption/decryption", "[vigenere]")
{
    const std::string key{"hello"};
    const std::string plainText{
        "THISISQUITEALONGMESSAGESOTHEKEYWILLNEEDTOREPEATAFEWTIMES"};
    const std::string cipherText{
        "ALTDWZUFTHLEWZBNQPDGHKPDCALPVSFATWZUIPOHVVPASHXLQSDXTXSZ"};

    REQUIRE_NOTHROW(constructVigenereCipher(key));
    VigenereCipher vc{key};

    SECTION("encryption")
    {
        REQUIRE(vc.applyCipher(plainText, CipherMode::Encrypt) == cipherText);
    }
    SECTION("decryption")
    {
        REQUIRE(vc.applyCipher(cipherText, CipherMode::Decrypt) == plainText);
    }
}

TEST_CASE("Vigenere Cipher bad key", "[vigenere]")
{
    REQUIRE_THROWS_AS(constructVigenereCipher(""), InvalidKey);
    REQUIRE_THROWS_AS(constructVigenereCipher(",./"), InvalidKey);
    REQUIRE_THROWS_AS(constructVigenereCipher("123"), InvalidKey);
}