#include <catch2/catch.hpp>

#include <qm/services/converters/NetworkToGraph.hpp>
#include <qm/models/Network.hpp>

using namespace qm;
using namespace std;

TEST_CASE("ConvertNetworkToGraph - One Node network", "[services][converters]") {
    vector<shared_ptr<models::Node>> nodes = {make_shared<models::Node>()};
    vector<shared_ptr<models::Connection>> connections{};
    qm::models::Network network{nodes, connections};

    const auto actual = services::converters::ConvertNetworkToGraph(network);
    const auto &vertices = actual.GetVertices();

    REQUIRE(vertices.size() == 1);
    REQUIRE(vertices[0]->GetBackingNode() == nodes[0]);
}

TEST_CASE("ConvertNetworkToGraph - Two Node network", "[services][converters]") {
    vector<shared_ptr<models::Node>> nodes = {
      make_shared<models::Node>(),
      make_shared<models::Node>()
    };

    shared_ptr<models::PointToPointConnection> p2p = make_shared<models::PointToPointConnection>();
    p2p->GetNodes() = nodes;

    vector<shared_ptr<models::Connection>> connections{p2p};

    qm::models::Network network{nodes, connections};

    const auto actual = services::converters::ConvertNetworkToGraph(network);
    const auto vertices = actual.GetVertices();

    REQUIRE(vertices.size() == 2);
    REQUIRE(vertices[0]->GetBackingNode() == nodes[0]);
    REQUIRE(vertices[0]->GetEdges().size() == 1);
    REQUIRE(vertices[0]->GetEdges()[0]->GetStartVertex().lock() == vertices[0]);
    REQUIRE(vertices[0]->GetEdges()[0]->GetEndVertex().lock() == vertices[1]);

    REQUIRE(vertices[1]->GetBackingNode() == nodes[1]);
    REQUIRE(vertices[1]->GetEdges()[0] == vertices[0]->GetEdges()[0]);

    REQUIRE(actual.GetEdges().size() == 1);
    REQUIRE(actual.GetEdges()[0]->GetBackingEdge() == p2p);
    REQUIRE(vertices[1]->GetEdges()[0] == actual.GetEdges()[0]);
}

// TODO add more tests
