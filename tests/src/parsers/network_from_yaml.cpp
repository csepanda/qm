#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>
#include <catch2/catch.hpp>
#include <qm/parsers.hpp>

static const std::string validYamlWithIdsAndReferences = R"(
nodes:
  - id: node01
    ipConfig:
      - address: 10.0.1.3/24
        connection: !Ref connection01
  - id: node02
    ipConfig:
      - address: 10.0.1.4/24
        connection: !Ref connection01
connections:
  - id: connection01
    type: P2P
    targets:
      - !Ref node01
      - !Ref node02
    dataRate: 5Mbps
    delay: 1ms
    mtu: 1500
)";

TEST_CASE("parse Network from valid yaml // correct nodes filling", "[parsers][yaml]") {
    const YAML::Node yaml = YAML::Load(validYamlWithIdsAndReferences);
    const auto actual = yaml.as<qm::parsers::yaml::NetworkYamlDTO>();

    REQUIRE(actual.NodesDTO.size() == 2);
    REQUIRE(actual.NodesDTO.at("node01").GetId() == "node01");
    REQUIRE(actual.NodesDTO.at("node02").GetId() == "node02");
}

TEST_CASE("parse Network from valid yaml // correct connections filling", "[parsers][yaml]") {
    const YAML::Node yaml = YAML::Load(validYamlWithIdsAndReferences);
    const auto actual = yaml.as<qm::parsers::yaml::NetworkYamlDTO>();

    REQUIRE(actual.ConnectionsDTO.size() == 1);
    REQUIRE(actual.ConnectionsDTO.at("connection01").GetId() == "connection01");
}

TEST_CASE("parse Network from valid yaml // references resolving in nodes", "[parsers][yaml]") {
    const YAML::Node yaml = YAML::Load(validYamlWithIdsAndReferences);
    const auto actual = yaml.as<qm::parsers::yaml::NetworkYamlDTO>();

    for (const auto&[id, node] : actual.NodesDTO) {
        const qm::parsers::yaml::NodeYamlDTO n = node;

        for (const auto &ipConfig : n.Node->GetIpConfigs()) {
            REQUIRE(ipConfig->BindConnection != nullptr);
        }

        for (const auto &ipConfigDTO : n.IpConfigs) {
            REQUIRE(ipConfigDTO.ConnectionRef.Resolved);
        }
    }
}

TEST_CASE("parse Network from valid yaml // references resolving in connections", "[parsers][yaml]") {
    const YAML::Node yaml = YAML::Load(validYamlWithIdsAndReferences);
    const auto actual = yaml.as<qm::parsers::yaml::NetworkYamlDTO>();

    for (const auto&[id, connection] : actual.ConnectionsDTO) {
        const auto nodes = connection.GetConnection()->GetNodes();

        REQUIRE(!nodes.empty());
        for (const auto &node : nodes) {
            REQUIRE(node != nullptr);
        }

        for (const auto &ref : connection.TargetsRefs) {
            REQUIRE(ref.Resolved);
        }
    }
}

TEST_CASE("parse Network from valid yaml // generate missing id", "[parsers][yaml]") {
    const YAML::Node yaml = YAML::Load(R"(
connections:
  - type: P2P
    dataRate: 5Mbps
    delay: 1ms
    mtu: 1500
)");

    const auto actual = yaml.as<qm::parsers::yaml::NetworkYamlDTO>();

    REQUIRE(actual.ConnectionsDTO.size() == 1);

    for (const auto&[key, connection] : actual.ConnectionsDTO) {
        const std::string id = connection.GetId();

        REQUIRE(key == id);

        boost::uuids::uuid uuid{};

        REQUIRE_NOTHROW(uuid = boost::lexical_cast<boost::uuids::uuid, std::string>(id));
    }
}


template<typename T>
static std::shared_ptr<T> findById(const std::vector<std::shared_ptr<T>> &collection, const std::string &id) {
    const auto iteratorPtr = std::find_if(collection.begin(), collection.end(),
      [id](const std::shared_ptr<T> &x) {
        return x->GetId() == id;
    });

    REQUIRE(iteratorPtr != collection.end());

    return *iteratorPtr;
}


TEST_CASE("parse Network from valid yaml // Final object", "[parsers][yaml]") {
    const YAML::Node yaml = YAML::Load(validYamlWithIdsAndReferences);
    const auto networkDTO = yaml.as<qm::parsers::yaml::NetworkYamlDTO> ();
    const qm::models::Network actual = networkDTO.GetNetwork();

    const auto &actualNodes = actual.GetNodes();
    const auto &actualConnections = actual.GetConnections();

    REQUIRE(actualNodes.size() == 2);
    REQUIRE(actualConnections.size() == 1);

    const auto node01 = findById(actualNodes, "node01");
    const auto node02 = findById(actualNodes, "node02");
    const auto connection01 = findById(actualConnections, "connection01");

    SECTION("Check references in connection") {
        const auto &nodesInConnection = connection01->GetNodes();
        REQUIRE(nodesInConnection.size() == 2);

        REQUIRE(std::find(nodesInConnection.begin(), nodesInConnection.end(), node01) != nodesInConnection.end());
        REQUIRE(std::find(nodesInConnection.begin(), nodesInConnection.end(), node02) != nodesInConnection.end());
    }

    SECTION("Check references in node01") {
        REQUIRE(node01->GetIpConfigs().size() == 1);

        const auto ipConfig = node01->GetIpConfigs()[0];
        REQUIRE(ipConfig->BindConnection == connection01);
    }

    SECTION("Check references in node02") {
        REQUIRE(node02->GetIpConfigs().size() == 1);

        const auto ipConfig = node02->GetIpConfigs()[0];
        REQUIRE(ipConfig->BindConnection == connection01);
    }
}
