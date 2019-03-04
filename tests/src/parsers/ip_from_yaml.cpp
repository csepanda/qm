#include <catch2/catch.hpp>
#include <qm/parsers.hpp>
#include <yaml-cpp/yaml.h>

static const auto validAddressesYaml = R"(
current: 0.0.0.0
loopback: 127.0.0.1
arbitrary: 53.32.46.17
broadcast: 255.255.255.255
)";

static const auto invalidAddressesYaml = R"(
current: 0..0.0
loopback: 256.0.0.1
arbitrary: foobar
broadcast: 255.1024.255.255
)";

static const auto validNetworksYaml = R"(
current: 0.0.0.0/24
loopback: 127.0.0.1/16
arbitrary: 53.32.46.17/16
broadcast: 255.255.255.255/0
)";

static const auto invalidNetworksYaml = R"(
current: 0..0.0/24
loopback: 256.0.0.1/16
arbitrary: foobar/24
broadcast: 255.1024.255.255/16
)";

TEST_CASE("parse IPv4 Address from valid yaml", "[parsers][yaml]") {
    const YAML::Node ipAddresses = YAML::Load(validAddressesYaml);
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
    const YAML::Node ipAddresses = YAML::Load(invalidAddressesYaml);

    for (const auto& key : {"current", "loopback", "arbitrary", "broadcast"}) {
        SECTION(key) {
            const auto inputNode = ipAddresses[key];

            REQUIRE_THROWS_AS(inputNode.as<qm::parsers::yaml::IPAddressYamlDTO>(), qm::parsers::ParseException);
        }
    }
}

TEST_CASE("parse IPv4 Network from valid yaml", "[parsers][yaml]") {
    const YAML::Node ipAddresses = YAML::Load(validNetworksYaml);

    for (const auto& key : {"current", "loopback", "arbitrary", "broadcast"}) {
        SECTION(key) {
            const auto inputNode = ipAddresses[key];
            const auto actual = inputNode.as<qm::parsers::yaml::IPNetworkYamlDTO>();

            REQUIRE(actual.ProtocolVersion == qm::models::IPv4);
            REQUIRE(actual.IPv4->GetNetworkStr() == inputNode.as<std::string>());
        }
    }
}

TEST_CASE("try to parse IPv4 Network from invalid yaml", "[parsers][yaml]") {
    const YAML::Node ipAddresses = YAML::Load(invalidNetworksYaml);

    for (const auto& key : {"current", "loopback", "arbitrary", "broadcast"}) {
        SECTION(key) {
            const auto inputNode = ipAddresses[key];

            REQUIRE_THROWS_AS(inputNode.as<qm::parsers::yaml::IPNetworkYamlDTO>(), qm::parsers::ParseException);
        }
    }
}
