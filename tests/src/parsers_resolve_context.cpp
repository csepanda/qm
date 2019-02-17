#include <catch2/catch.hpp>
#include <qm/parsers.hpp>
#include <yaml-cpp/yaml.h>

using Context = qm::parsers::yaml::YamlContextDTO;
using NodeDTO = qm::parsers::yaml::NodeYamlDTO;
using ConnectionDTO = qm::parsers::yaml::ConnectionYamlDTO;
using IpConfigDTO = qm::parsers::yaml::IpConfigYamlDTO;
using YamlReference = qm::parsers::yaml::YamlReference;
using Node = qm::models::Node;
using IpConfig = qm::models::IpConfig;
using P2PConnection = qm::models::PointToPointConnection;

static NodeDTO createNode(std::string nodeId) {
    NodeDTO nodeDTO{};
    nodeDTO.Node = std::make_shared<Node>();
    nodeDTO.Node->SetId(std::move(nodeId));

    return nodeDTO;
}

static IpConfigDTO createIpConfig(std::string connectionId) {
    IpConfigDTO ipConfigDTO {};
    ipConfigDTO.ConnectionRef.Id = std::move(connectionId);

    return ipConfigDTO;
}

static ConnectionDTO createConnection(std::string connectionId, std::vector<std::string> targetRefs) {
    ConnectionDTO connectionDTO{};
    connectionDTO.p2p = std::make_shared<P2PConnection>();
    connectionDTO.p2p->SetId(std::move(connectionId));

    for (auto& ref : targetRefs) {
        YamlReference reference{};
        reference.Id = ref;

        connectionDTO.TargetsRefs.push_back(reference);
    }

    return connectionDTO;
}

static const std::string id_node01 = "node01";
static const std::string id_connection01 = "connection01";

static Context prepareContext_valid();
TEST_CASE("resolveContext // valid context", "[parsers][yaml]") {
    SECTION("default") {
        Context ctx = prepareContext_valid();
        ctx.ResolveContext();

        auto node01 = ctx.NodesDTO[id_node01];
        auto connection01 = ctx.ConnectionsDTO[id_connection01];

        SECTION("verify resolved context") {
            REQUIRE(connection01.p2p->GetNodes().size() == 1);
            REQUIRE(connection01.p2p->GetNodes()[0] == node01.Node);
            REQUIRE(node01.IpConfigs[0].IpConfig.BindConnection == connection01.p2p);
            REQUIRE(node01.Node->GetIpConfigs().size() == 1);
            REQUIRE(node01.Node->GetIpConfigs()[0].BindConnection == connection01.p2p);
        }
    }
}

static Context prepareContext_noBackReference();
TEST_CASE("resolveContext // no back reference", "[parsers][yaml]") {
    SECTION("exception") {
        Context ctx = prepareContext_noBackReference();
        REQUIRE_THROWS_AS(ctx.ResolveContext(), qm::parsers::ParseException);
    }

    SECTION("message") {
        Context ctx = prepareContext_noBackReference();
        REQUIRE_THROWS_WITH(ctx.ResolveContext(), "Object with id 'connection01' has no back reference");
    }
}

static Context prepareContext_allReferencesUsed();
TEST_CASE("resolveContext // all references are used", "[parsers][yaml]") {
    SECTION("exception") {
        Context ctx = prepareContext_allReferencesUsed();
        REQUIRE_THROWS_AS(ctx.ResolveContext(), qm::parsers::ParseException);
    }

    SECTION("message") {
        Context ctx = prepareContext_allReferencesUsed();
        REQUIRE_THROWS_WITH(ctx.ResolveContext(), "Found 1 already resolved refs of object with id 'connection01'");
    }
}

static Context prepareContext_valid() {
    Context ctx{};

    auto node01 = createNode(id_node01);
    auto connection01 = createConnection(id_connection01, {id_node01});

    node01.IpConfigs.push_back(createIpConfig(id_connection01));
    ctx.NodesDTO[id_node01] = node01;
    ctx.ConnectionsDTO[id_connection01] = connection01;

    SECTION("verify initial test case configuration") {
        REQUIRE(connection01.p2p->GetNodes().empty());
        REQUIRE(connection01.TargetsRefs.size() == 1);
        REQUIRE(connection01.TargetsRefs[0].Id == id_node01);
        REQUIRE(node01.IpConfigs.size() == 1);
        REQUIRE(node01.IpConfigs[0].ConnectionRef.Id == id_connection01);
        REQUIRE(node01.IpConfigs[0].IpConfig.BindConnection == nullptr);
        REQUIRE(node01.Node->GetIpConfigs().empty());
    }

    return ctx;
}

static Context prepareContext_noBackReference() {
    Context ctx{};

    auto node01 = createNode(id_node01);
    auto connection01 = createConnection(id_connection01, {});

    node01.IpConfigs.push_back(createIpConfig(id_connection01));
    ctx.NodesDTO[id_node01] = node01;
    ctx.ConnectionsDTO[id_connection01] = connection01;

    SECTION("verify initial test case configuration") {
        REQUIRE(connection01.p2p->GetNodes().empty());
        REQUIRE(connection01.TargetsRefs.empty());
        REQUIRE(node01.IpConfigs.size() == 1);
        REQUIRE(node01.IpConfigs[0].ConnectionRef.Id == id_connection01);
        REQUIRE(node01.IpConfigs[0].IpConfig.BindConnection == nullptr);
        REQUIRE(node01.Node->GetIpConfigs().empty());
    }

    return ctx;
}

static Context prepareContext_allReferencesUsed() {
    Context ctx{};

    auto node01 = createNode(id_node01);
    auto connection01 = createConnection(id_connection01, {id_node01});

    node01.IpConfigs.push_back(createIpConfig(id_connection01));
    node01.IpConfigs.push_back(createIpConfig(id_connection01));
    ctx.NodesDTO[id_node01] = node01;
    ctx.ConnectionsDTO[id_connection01] = connection01;

    SECTION("verify initial test case configuration") {
        REQUIRE(connection01.p2p->GetNodes().empty());
        REQUIRE(connection01.TargetsRefs.size() == 1);
        REQUIRE(connection01.TargetsRefs[0].Id == id_node01);
        REQUIRE(node01.IpConfigs.size() == 2);
        REQUIRE(node01.IpConfigs[0].ConnectionRef.Id == id_connection01);
        REQUIRE(node01.IpConfigs[0].IpConfig.BindConnection == nullptr);
        REQUIRE(node01.IpConfigs[1].ConnectionRef.Id == id_connection01);
        REQUIRE(node01.IpConfigs[1].IpConfig.BindConnection == nullptr);
        REQUIRE(node01.Node->GetIpConfigs().empty());
    }

    return ctx;
}
