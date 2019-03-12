#include <catch2/catch.hpp>
#include <qm/parsers.hpp>

TEST_CASE("Node yaml parsing/Valid yaml/All fields", "[parsers][yaml]") {
    const YAML::Node yaml = YAML::Load(R"(
node:
    id: testNode
    ipConfig:
      - address: 10.0.1.3/24
        connection: !Ref connection_01
    files:
      - path: /etc/foo/bar.cfg
        text: |
          debug=true
          logLevel=verbose
)");

    const auto actual = yaml["node"].as<qm::yaml::dto::Node>();

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

    SECTION("Files check") {
        const auto &files = actual.Node->GetFiles();

        SECTION("files count == 1") {
            REQUIRE(files.size() == 1);
        }

        SECTION("file's path is correct") {
            REQUIRE(files[0]->GetPath() == "/etc/foo/bar.cfg");
        }
    }
}

TEST_CASE("Node yaml parsing/Valid yaml/Files are nto required", "[parsers][yaml]") {
    const YAML::Node yaml = YAML::Load(R"(
node:
    id: testNode
    ipConfig:
      - address: 10.0.1.3/24
        connection: !Ref connection_01
)");

    REQUIRE_NOTHROW(yaml["node"].as<qm::yaml::dto::Node>());
}

TEST_CASE("parse Node from yaml with invalid non-sequence ipConfig", "[parsers][yaml]") {
    const YAML::Node yaml = YAML::Load(R"(
node:
    id: testNode
    ipConfig:
        address: 10.0.1.3/24
        connection: !Ref connection_01
)");

    REQUIRE_THROWS(yaml["node"].as<qm::yaml::dto::Node>());
}
