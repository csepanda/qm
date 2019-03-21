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
#include "File.hpp"
#include "ip.hpp"

namespace qm::models {

class Connection;

class File;

struct IpConfig {
    std::shared_ptr<IPNetwork> Address;
    std::shared_ptr<Connection> BindConnection;

    ns3::Ptr<ns3::NetDevice> NS3NetDevice;
};

class Node : public Identifiable {
    uint32_t m_systemId;
    ns3::Ptr<ns3::Node> m_ns3_node;
    std::vector<std::unique_ptr<File>> m_files{};
    std::vector<std::shared_ptr<IpConfig>> m_ipConfigs{};

public:
    const ns3::Ptr<ns3::Node> &GetNS3Node() const;

    const std::vector<std::shared_ptr<IpConfig>> &GetIpConfigs() const;

    const std::vector<std::unique_ptr<File>> &GetFiles() const;

    const uint32_t GetSystemId() const;

    void AddIpConfig(std::shared_ptr<IpConfig> ipConfig);

    void AddFile(std::unique_ptr<File> file);

    void SetNS3Node(const ns3::Ptr<ns3::Node> &NS3Node);

    void SetSystemId(uint32_t systemId);

    const std::shared_ptr<IpConfig> &FindIpConfig(const std::shared_ptr<Connection> &connection) const;
};

}

#endif
