#ifndef QM_NETWORK_H
#define QM_NETWORK_H

#include "ns3/node.h"
#include "ns3/ptr.h"

#include "node.hpp"
#include "connections.hpp"


namespace qm::models {
class Network {
    std::vector<std::shared_ptr<Node>> m_nodes;
    std::vector<std::shared_ptr<Connection>> m_connections;
    std::vector<std::vector<uint32_t>> m_adjacencyList;
public:
    Network(std::vector<std::shared_ptr<Node>> &nodes, std::vector<std::shared_ptr<Connection>> &connections);
};

}

#endif //QM_NETWORK_H
