//! Unit Tests for MPAGSCipher CaesarCipher Class
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "CaesarCipher.hpp"

// Needs to use a lambda for the constructor to use it in REQUIRE_THROWS_AS and REQUIRE_NOTHROW
auto constructCaesarCipher = [](const std::string& key) {
    CaesarCipher cc{key};
};

TEST_CASE("Caesar Cipher encryption/decryption", "[caesar]")
{
    const std::size_t key{10};
    const std::string keyStr{"10"};

    REQUIRE_NOTHROW(constructCaesarCipher(keyStr));

    CaesarCipher cc1{key};
    CaesarCipher cc2{keyStr};

    const std::string plainText{"HELLOWORLD"};
    const std::string cipherText{"ROVVYGYBVN"};

    SECTION("encryption")
    {
        REQUIRE(cc1.applyCipher(plainText, CipherMode::Encrypt) == cipherText);
        REQUIRE(cc2.applyCipher(plainText, CipherMode::Encrypt) == cipherText);
    }

    SECTION("decryption")
    {
        REQUIRE(cc1.applyCipher(cipherText, CipherMode::Decrypt) == plainText);
        REQUIRE(cc2.applyCipher(cipherText, CipherMode::Decrypt) == plainText);
    }
}

TEST_CASE("Caesar Cipher negative key", "[caesar]")
{
    REQUIRE_THROWS_AS(constructCaesarCipher("-9"), InvalidKey);
}

TEST_CASE("Caesar Cipher non-numeric key", "[caesar]")
{
    REQUIRE_THROWS_AS(constructCaesarCipher("hello"), InvalidKey);
}

TEST_CASE("Caesar Cipher too large a key", "[caesar]")
{
    REQUIRE_THROWS_AS(constructCaesarCipher("98765432112345678987654321123456789"),
                      InvalidKey);
} 
