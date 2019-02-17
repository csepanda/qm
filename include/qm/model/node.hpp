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

#include "identifiable.hpp"
#include "connections.hpp"
#include "ip.hpp"

namespace qm::models {

class Connection;

struct IpConfig {
    std::shared_ptr<IPNetwork> Address;
    std::shared_ptr<Connection> BindConnection;
};

class Node : public Identifiable {
    ns3::Ptr<ns3::Node> m_ns3_node;
    std::vector<IpConfig> m_ipConfigs{};

public:
    const ns3::Ptr<ns3::Node> &GetNS3Node() const;

    void SetNS3Node(const ns3::Ptr<ns3::Node> &NS3Node);

    const std::vector<IpConfig> &GetIpConfigs() const;

    void AddIpConfig(IpConfig ipConfig);
};

}

#endif
