#ifndef QM_MODEL_NODE_H
#define QM_MODEL_NODE_H

#include <memory>
#include <array>
#include <map>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <ns3/attribute.h>
#include <ns3/data-rate.h>
#include <ns3/node.h>
#include <ns3/ptr.h>
#include <ns3/uinteger.h>

#include "connections.hpp"
#include "ip.hpp"

namespace qm::models {

class Connection;

class IpConfig {
    std::shared_ptr<Connection> connection;
    std::unique_ptr<IPNetwork> address;
};

class Node {
    ns3::Ptr<ns3::Node> ns3_node;
    std::vector<IpConfig> m_ip_configs;
public:
    void setNS3Node(ns3::Ptr<ns3::Node> node);
    ns3::Ptr<ns3::Node> getNS3Node();
};

}

#endif
