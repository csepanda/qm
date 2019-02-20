#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>
#include <catch2/catch.hpp>
#include <qm/parsers.hpp>

TEST_CASE("parse Network from valid yaml", "[parsers][yaml]") {
    const YAML::Node yaml = YAML::Load(R"(
nodes:
  - id: node01
    ipConfig:
      - address: 10.0.1.3/24
        connection: !Ref connection_01
  - id: node02
    ipConfig:
      - address: 10.0.1.4/24
        connection: !Ref connection_01
connections:
  - id: connection01
    type: P2P
    target:
      - !Ref node01
      - !Ref node02
    dataRate: 5Mbps
    delay: 1ms
    mtu: 1500
)");

    const auto actual = yaml.as<qm::parsers::yaml::NetworkYamlDTO>();

    SECTION("ASSERT NODES") {
        REQUIRE(actual.NodesDTO.size() == 2);
        REQUIRE(actual.NodesDTO.at("node01").GetId() == "node01");
        REQUIRE(actual.NodesDTO.at("node02").GetId() == "node02");
    }

    SECTION("ASSERT CONNECTIONS") {
        REQUIRE(actual.ConnectionsDTO.size() == 1);
        REQUIRE(actual.ConnectionsDTO.at("connection01").GetId() == "connection01");
    }
}

TEST_CASE("parse Network from valid yaml // generate missing id", "[parsers][yaml]") {
    const YAML::Node yaml = YAML::Load(R"(
connections:
  - type: P2P
    target:
      - !Ref node01
      - !Ref node02
    dataRate: 5Mbps
    delay: 1ms
    mtu: 1500
)");

    const auto actual = yaml.as<qm::parsers::yaml::NetworkYamlDTO>();

    REQUIRE(actual.ConnectionsDTO.size() == 1);

    for (const auto& [key, connection] : actual.ConnectionsDTO) {
        const std::string id = connection.GetId();

        REQUIRE(key == id);

        boost::uuids::uuid uuid{};

        REQUIRE_NOTHROW(uuid = boost::lexical_cast<boost::uuids::uuid, std::string>(id));
    }
}
