#include <qm/exceptions.hpp>
#include <qm/model.hpp>
#include <qm/model/network.hpp>
#include <algorithm>

namespace qm::models {
Network::Network(std::vector<std::shared_ptr<Node>> &nodes, std::vector<std::shared_ptr<Connection>> &connections) {
    m_connections = connections;
    m_nodes = nodes;
}

const std::vector<std::shared_ptr<Node>> &Network::GetNodes() const {
    return m_nodes;
}

const std::vector<std::shared_ptr<Connection>> &Network::GetConnections() const {
    return m_connections;
}

const std::shared_ptr<Node> &Network::FindNode(const ns3::Ptr<ns3::Node> &ns3) const {
    const auto iterPtr = std::find_if(m_nodes.begin(), m_nodes.end(), [ns3](const auto &node) {
        return node->GetNS3Node() == ns3;
    });

    return *iterPtr;
}

}
