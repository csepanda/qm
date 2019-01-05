#include <catch2/catch.hpp>
#include <qm/parsers.hpp>

TEST_CASE("parseCIDR/Parse valid input", "[parsers]") {
    SECTION("Numeric only for IPv6") {
        REQUIRE(qm::parsers::parseCIDR("128") == 128);
    }

    SECTION("Numeric for IPv4/IPv6") {
        REQUIRE(qm::parsers::parseCIDR("32") == 32);
        REQUIRE(qm::parsers::parseCIDR("16") == 16);
        REQUIRE(qm::parsers::parseCIDR("8") == 8);
        REQUIRE(qm::parsers::parseCIDR("3") == 3);
    }
}

TEST_CASE("parseCIDR/Throws ParseException on invalid input", "[parsers]") {
    REQUIRE_THROWS_AS(qm::parsers::parseCIDR("foobar"), qm::parsers::ParseException);
}

void parseIPv4AndAssert(const std::string &input, const std::array<uint8_t, 4> &expected) {
    std::array<uint8_t, 4> actual = qm::parsers::parseIPv4(input);

    REQUIRE(actual == expected);
}

TEST_CASE("parseIPv4/Parse valid input", "[parsers]") {
    SECTION("current network address") {
        parseIPv4AndAssert("0.0.0.0", {0, 0, 0, 0});
    }

    SECTION("localhost") {
        parseIPv4AndAssert("127.0.0.1", {127, 0, 0, 1});
    }

    SECTION("arbitrary") {
        parseIPv4AndAssert("45.176.1.200", {45, 176, 1, 200});
    }

    SECTION("broadcast") {
        parseIPv4AndAssert("255.255.255.255", {255, 255, 255, 255});
    }
}

TEST_CASE("parseIPv4/Invalid format", "[parsers]") {
    const auto expectedMessage = "doesn't match format: x.x.x.x";

    REQUIRE_THROWS_AS(qm::parsers::parseIPv4("127..0.0"), qm::parsers::ParseException);
    REQUIRE_THROWS_WITH(qm::parsers::parseIPv4("127..0.0"), expectedMessage);
    REQUIRE_THROWS_WITH(qm::parsers::parseIPv4("127.-1.0.0"), expectedMessage);

    REQUIRE_THROWS_WITH(qm::parsers::parseIPv4("..0.0"), expectedMessage);
    REQUIRE_THROWS_WITH(qm::parsers::parseIPv4("1::ffff"), expectedMessage);
    REQUIRE_THROWS_WITH(qm::parsers::parseIPv4("foobar"), expectedMessage);
}

TEST_CASE("parseIPv4/Wrong IPv4 components", "[parsers]") {
    const auto expectedMessage = "IPv4 component cannot contain numbers greater than 255 or less than zero";

    REQUIRE_THROWS_AS(qm::parsers::parseIPv4("127.256.0.1"), qm::parsers::ParseException);
    REQUIRE_THROWS_WITH(qm::parsers::parseIPv4("127.256.0.1"), expectedMessage);
    REQUIRE_THROWS_WITH(qm::parsers::parseIPv4("127.512.0.1"), expectedMessage);
}
