#include <catch2/catch.hpp>
#include <qm/parsers.hpp>

TEST_CASE("parse Node from valid yaml", "[parsers][yaml]") {
    const YAML::Node yaml = YAML::Load(R"(
node:
    id: testNode
    ipConfig:
      - address: 10.0.1.3/24
        connection: !Ref connection_01
)");

    const auto actual = yaml["node"].as<qm::parsers::yaml::NodeYamlDTO>();

    SECTION("Id of node is correctly parsed") {
        REQUIRE(actual.Node->GetId() == "testNode");
    }


    SECTION("Assert IpConfigs") {
        SECTION("After yaml parsing node has no resolved IpConfigs") {
            REQUIRE(actual.Node->GetIpConfigs().empty());
        }

        SECTION("After yaml parsing node has parsed IpConfigsDTO") {
            REQUIRE(actual.IpConfigs.size() == 1);

            const auto ipConfigDTO = actual.IpConfigs[0];

            SECTION("ConnectionReference is correctly parsed") {
                REQUIRE(ipConfigDTO.ConnectionRef.Id == "connection_01");
            }

            SECTION("Connection is null after parse") {
                REQUIRE(ipConfigDTO.IpConfig->BindConnection == nullptr);
            }

            SECTION("Address is correctly parsed") {
                REQUIRE(ipConfigDTO.IpConfig->Address->GetProtocolVersion() == qm::models::IPv4);
                REQUIRE(ipConfigDTO.IpConfig->Address->GetNetworkStr() == "10.0.1.3/24");
            }
        }
    }
}

TEST_CASE("parse Node from yaml with invalid non-sequence ipConfig", "[parsers][yaml]") {
    const YAML::Node yaml = YAML::Load(R"(
node:
    id: testNode
    ipConfig:
        address: 10.0.1.3/24
        connection: !Ref connection_01
)");

    REQUIRE_THROWS(yaml["node"].as<qm::parsers::yaml::NodeYamlDTO>());
}
