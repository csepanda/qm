#include <algorithm>

#include <qm/models.hpp>

namespace qm::models {
const ns3::Ptr<ns3::Node> &Node::GetNS3Node() const {
    return m_ns3_node;
}

void Node::AddIpConfig(std::shared_ptr<IpConfig> ipConfig) {
    this->m_ipConfigs.push_back(std::move(ipConfig));
}

const std::vector<std::shared_ptr<IpConfig>> &Node::GetIpConfigs() const {
    return m_ipConfigs;
}

void Node::SetNS3Node(const ns3::Ptr<ns3::Node> &NS3Node) {
    this->m_ns3_node = NS3Node;
}

const std::shared_ptr<IpConfig> &Node::FindIpConfig(const std::shared_ptr<Connection> &connection) const {
    const auto iterPtr = std::find_if(m_ipConfigs.begin(), m_ipConfigs.end(), [connection](auto &ipc) {
        return ipc->BindConnection == connection;
    });

    return *iterPtr;
}
}