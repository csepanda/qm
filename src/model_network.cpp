#include <ns3/point-to-point-helper.h>
#include <ns3/node-container.h>
#include <qm/exceptions.hpp>
#include <qm/model.hpp>

namespace qm::models {
void configureP2PConnection(const std::shared_ptr<PointToPointConnection> &connection) {
    ns3::NodeContainer net{};

    const auto nodes = connection->GetNodes();

    if (nodes.size() != 2) {
        throw InitializationException("P2P connection cannot handle less or greater than 2 nodes",
                                      "P2PConnection::Initialization");
    }
    for (const auto &node : nodes) {
        net.Add(node->GetNS3Node());
    }

    ns3::PointToPointHelper helper;

    helper.Install(net);
}

Network::Network(std::vector<std::shared_ptr<Node>> &nodes, std::vector<std::shared_ptr<Connection>> &connections) {
    for (const auto &connection : connections) {
        switch (connection->GetConnectionType()) {
            case ConnectionType::P2P: {
                const auto p2pConnection = std::dynamic_pointer_cast<PointToPointConnection>(connection);

                configureP2PConnection(p2pConnection);
                break;
            }
            default:
                throw InitializationException("", "");
        }
    }
    m_connections = connections;
    m_nodes = nodes;
}


}
