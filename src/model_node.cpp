#include <qm/model.hpp>

namespace qm::models {
const ns3::Ptr<ns3::Node> &Node::GetNS3Node() const {
    return m_ns3_node;
}

void Node::AddIpConfig(IpConfig ipConfig) {
    this->m_ipConfigs.push_back(std::move(ipConfig));
}

const std::vector<IpConfig> &Node::GetIpConfigs() const {
    return m_ipConfigs;
}

void Node::SetNS3Node(const ns3::Ptr<ns3::Node> &NS3Node) {
    this->m_ns3_node = NS3Node;
}
}