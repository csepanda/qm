#include <catch2/catch.hpp>
#include <qm/parsers/IpUtils.hpp>
#include <qm/parsers.hpp>

TEST_CASE("parseCIDR/Parse valid input", "[parsers]") {
    SECTION("Numeric only for IPv6") {
        REQUIRE(qm::parsers::IpUtils::parseCIDR("128") == 128);
    }

    SECTION("Numeric for IPv4/IPv6") {
        REQUIRE(qm::parsers::IpUtils::parseCIDR("32") == 32);
        REQUIRE(qm::parsers::IpUtils::parseCIDR("16") == 16);
        REQUIRE(qm::parsers::IpUtils::parseCIDR("8") == 8);
        REQUIRE(qm::parsers::IpUtils::parseCIDR("3") == 3);
    }
}

TEST_CASE("parseCIDR/Throws ParseException on invalid input", "[parsers]") {
    REQUIRE_THROWS_AS(qm::parsers::IpUtils::parseCIDR("foobar"), qm::parsers::ParseException);
}

void parseIPv4AndAssert(const std::string &input, const std::array<uint8_t, 4> &expected) {
    std::array<uint8_t, 4> actual = qm::parsers::IpUtils::parseIPv4(input);

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

    REQUIRE_THROWS_AS(qm::parsers::IpUtils::parseIPv4("127..0.0"), qm::parsers::ParseException);
    REQUIRE_THROWS_WITH(qm::parsers::IpUtils::parseIPv4("127..0.0"), expectedMessage);
    REQUIRE_THROWS_WITH(qm::parsers::IpUtils::parseIPv4("127.-1.0.0"), expectedMessage);

    REQUIRE_THROWS_WITH(qm::parsers::IpUtils::parseIPv4("..0.0"), expectedMessage);
    REQUIRE_THROWS_WITH(qm::parsers::IpUtils::parseIPv4("1::ffff"), expectedMessage);
    REQUIRE_THROWS_WITH(qm::parsers::IpUtils::parseIPv4("foobar"), expectedMessage);
}

TEST_CASE("parseIPv4/Wrong IPv4 components", "[parsers]") {
    const auto expectedMessage = "IPv4 component cannot contain numbers greater than 255 or less than zero";

    REQUIRE_THROWS_AS(qm::parsers::IpUtils::parseIPv4("127.256.0.1"), qm::parsers::ParseException);
    REQUIRE_THROWS_WITH(qm::parsers::IpUtils::parseIPv4("127.256.0.1"), expectedMessage);
    REQUIRE_THROWS_WITH(qm::parsers::IpUtils::parseIPv4("127.512.0.1"), expectedMessage);
}

TEST_CASE("determineIPVersion/IPv4 input", "[parsers]") {
    REQUIRE(qm::parsers::IpUtils::determineIPVersion("0.0.0.0") == qm::models::IPv4);
    REQUIRE(qm::parsers::IpUtils::determineIPVersion("8.8.8.8") == qm::models::IPv4);
    REQUIRE(qm::parsers::IpUtils::determineIPVersion("127.0.0.1") == qm::models::IPv4);
    REQUIRE(qm::parsers::IpUtils::determineIPVersion("176.16.1.2") == qm::models::IPv4);
    REQUIRE(qm::parsers::IpUtils::determineIPVersion("255.255.255.255") == qm::models::IPv4);
}

TEST_CASE("determineIPVersion/Invalid input", "[parsers]") {
    const auto expectedMessage = "Unknown IP address protocol version";

    REQUIRE_THROWS_AS(qm::parsers::IpUtils::determineIPVersion("127..0.1"), qm::parsers::ParseException);
    REQUIRE_THROWS_WITH(qm::parsers::IpUtils::determineIPVersion(".56.0.1"), expectedMessage);
    REQUIRE_THROWS_WITH(qm::parsers::IpUtils::determineIPVersion("foobar"), expectedMessage);
}

TEST_CASE("determineIPVersion/IPv6 input", "[parsers]") {
    REQUIRE(qm::parsers::IpUtils::determineIPVersion("::") == qm::models::IPv6);
    REQUIRE(qm::parsers::IpUtils::determineIPVersion("ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff") == qm::models::IPv6);
    REQUIRE(qm::parsers::IpUtils::determineIPVersion("::1") == qm::models::IPv6);
    REQUIRE(qm::parsers::IpUtils::determineIPVersion("::ffff:0.0.0.0") == qm::models::IPv6);
    REQUIRE(qm::parsers::IpUtils::determineIPVersion("2001:db8::") == qm::models::IPv6);
}

TEST_CASE("parse IPv4 Network from invalid format string", "[parsers][yaml]") {
    const YAML::Node yaml = YAML::Load("192.168.0.1");

    REQUIRE_THROWS_AS(yaml.as<qm::parsers::yaml::IPNetworkYamlDTO>(), qm::parsers::ParseException);
}

TEST_CASE("parse IPv4 Network from string with invalid cidr value", "[parsers][yaml]") {
    const YAML::Node yaml = YAML::Load("192.168.0.1/64");

    REQUIRE_THROWS_AS(yaml.as<qm::parsers::yaml::IPNetworkYamlDTO>(), std::invalid_argument);
}

TEST_CASE("parse IPv4 Network from string with invalid cidr", "[parsers][yaml]") {
    const YAML::Node yaml = YAML::Load("192.168.0.1/dasd");

    REQUIRE_THROWS_AS(yaml.as<qm::parsers::yaml::IPNetworkYamlDTO>(), qm::parsers::ParseException);
}
