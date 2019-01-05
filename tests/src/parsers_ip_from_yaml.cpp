#include <catch2/catch.hpp>
#include <qm/parsers.hpp>
#include <yaml-cpp/yaml.h>

TEST_CASE("parse IPv4 Address from valid yaml", "[parsers][yaml]") {
    const YAML::Node ipAddresses = YAML::Load(R"(
current: 0.0.0.0
loopback: 127.0.0.1
arbitrary: 53.32.46.17
broadcast: 255.255.255.255
)");

    for (const auto& key : {"current", "loopback", "arbitrary", "broadcast"}) {
        SECTION(key) {
            const auto inputNode = ipAddresses[key];
            const auto actual = inputNode.as<qm::parsers::yaml::IPAddressYamlDTO>();

            REQUIRE(actual.ProtocolVersion == qm::models::IPv4);
            REQUIRE(actual.IPv4.GetAddressStr() == inputNode.as<std::string>());
        }
    }
}

TEST_CASE("try to parse IPv4 Address from invalid yaml", "[parsers][yaml]") {
    const YAML::Node ipAddresses = YAML::Load(R"(
current: 0..0.0
loopback: 256.0.0.1
arbitrary: foobar
broadcast: 255.1024.255.255
)");

    for (const auto& key : {"current", "loopback", "arbitrary", "broadcast"}) {
        SECTION(key) {
            const auto inputNode = ipAddresses[key];

            REQUIRE_THROWS_AS(inputNode.as<qm::parsers::yaml::IPAddressYamlDTO>(), qm::parsers::ParseException);
        }
    }

}
