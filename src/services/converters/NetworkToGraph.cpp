#include <memory>
#include <vector>
#include <qm/services/convertors/NetworkToGraph.hpp>

namespace qm::services::converters {
NetworkGraph ConvertNetworkToGraph(const qm::models::Network &network) {
    std::vector<std::shared_ptr<NetworkVertex>> vertices{};
    std::vector<std::shared_ptr<NetworkEdge>> edges{};

    std::map<std::shared_ptr<qm::models::Node>, std::shared_ptr<NetworkVertex>> lookupTable{};

    for (const auto &node : network.GetNodes()) {
        auto vertex = std::make_shared<NetworkVertex>(GetWeightFor(node), node);

        vertices.push_back(vertex);
        lookupTable[node] = vertex;
    }

    for (const auto &connection : network.GetConnections()) {
        switch (connection->GetConnectionType()) {
            case qm::models::ConnectionType::P2P: {
                const auto p2pConnection = std::dynamic_pointer_cast<qm::models::PointToPointConnection>(connection);

                const auto &startNode = p2pConnection->Nodes[0];
                const auto &endNode = p2pConnection->Nodes[1];

                if (startNode == nullptr || endNode == nullptr) {
                    throw std::logic_error("P2P connection's node should be set. ID: " + connection->GetId());
                }

                const auto &startVertex = lookupTable.at(startNode);
                const auto &endVertex = lookupTable.at(endNode);

                std::weak_ptr<NetworkVertex> startPtr = startVertex;
                std::weak_ptr<NetworkVertex> endPtr = endVertex;

                const auto weight = GetWeightFor(connection);
                const auto edge = std::make_shared<NetworkEdge>(weight, weight, startPtr, endPtr);

                startVertex->AddEdge(edge);
                endVertex->AddEdge(edge);

                edges.push_back(edge);
                break;
            }
            default:
                throw std::logic_error(
                  "Only P2P connection are supported for graph conversion. ID: " + connection->GetId()
                );
        }
    }

    return NetworkGraph(vertices, edges);
}

int GetWeightFor(const std::shared_ptr<qm::models::Node> &node) {
    return 0;
}

int GetWeightFor(const std::shared_ptr<qm::models::Connection> &connection) {
    return 0;
}

}

