#ifndef QM_NETWORK_H
#define QM_NETWORK_H

#include "ns3/node.h"
#include "ns3/ptr.h"

#include "Node.hpp"
#include "connections.hpp"


namespace qm::models {
class Network {
    std::vector<std::shared_ptr<Node>> m_nodes;
    std::vector<std::shared_ptr<Connection>> m_connections;
    std::vector<std::vector<uint32_t>> m_adjacencyList;
public:
    Network(std::vector<std::shared_ptr<Node>> &nodes, std::vector<std::shared_ptr<Connection>> &connections);

    const std::vector<std::shared_ptr<Node>> &GetNodes() const;

    const std::vector<std::shared_ptr<Connection>> &GetConnections() const;

    /**
     * Find node in network by its NS3 representation.
     * @param ns3Node
     * @return ptr to node if found otherwise nullptr
     */
    const std::shared_ptr<Node> &FindNode(const ns3::Ptr<ns3::Node> &ns3Node) const;
};

}

#endif //QM_NETWORK_H
