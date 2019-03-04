#include <catch2/catch.hpp>
#include <qm/parsers.hpp>

TEST_CASE("parse IpConfig from valid yaml", "[parsers][yaml]") {
    const YAML::Node yaml = YAML::Load(R"(
ipConfig:
    address: 10.0.1.3/24
    connection: !Ref connection_01
)");

    const auto actual = yaml["ipConfig"].as<qm::yaml::dto::IpConfigYamlDTO>();

    SECTION("ConnectionReference is correctly parsed") {
        REQUIRE(actual.ConnectionRef.Id == "connection_01");
    }

    SECTION("Connection is null after parse") {
        REQUIRE(actual.IpConfig->BindConnection == nullptr);
    }

    SECTION("Address is correctly parsed") {
        REQUIRE(actual.IpConfig->Address->GetProtocolVersion() == qm::models::IPv4);
        REQUIRE(actual.IpConfig->Address->GetNetworkStr() == "10.0.1.3/24");
    }
}

TEST_CASE("parse IpConfig from yaml with invalid address", "[parsers][yaml]") {
    const YAML::Node yaml = YAML::Load(R"(
ipConfig:
    address: 10.0..3/24
    connection: !Ref connection_01
)");

    REQUIRE_THROWS(yaml["ipConfig"].as<qm::yaml::dto::IpConfigYamlDTO>());
}

TEST_CASE("parse IpConfig from yaml with invalid connection reference", "[parsers][yaml]") {
    const YAML::Node yaml = YAML::Load(R"(
ipConfig:
    address: 10.0..3/24
    connection: !fef connection_01
)");

    REQUIRE_THROWS(yaml["ipConfig"].as<qm::yaml::dto::IpConfigYamlDTO>());
}

