#ifndef QM_MODEL_CONNECTION_H
#define QM_MODEL_CONNECTION_H

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

namespace qm::models {
class Node;

enum class ConnectionType {
    P2P
};

class Connection : public Identifiable {
public:
    virtual ConnectionType GetConnectionType() const = 0;

    virtual std::map<std::string, std::unique_ptr<ns3::AttributeValue> > GetChannelAttributes() const = 0;

    virtual std::map<std::string, std::unique_ptr<ns3::AttributeValue> > GetDeviceAttributes() const = 0;

    virtual std::vector<std::shared_ptr<Node>> &GetNodes() = 0;
};

class PointToPointConnection : public Connection {
private:
    ns3::UintegerValue m_mtu{};
    ns3::DataRateValue m_dataRate{};
    ns3::TimeValue m_delay{};
    std::vector<std::shared_ptr<Node>> m_nodes{};
public:
    std::vector<std::shared_ptr<Node>> Nodes;

    PointToPointConnection() = default;

    void setMtu(uint16_t t_mtu);

    void setDataRate(std::string t_dataRate);

    void setDelay(std::string t_delay);

    ConnectionType GetConnectionType() const override { return ConnectionType::P2P; };

    std::map<std::string, std::unique_ptr<ns3::AttributeValue> > GetChannelAttributes() const override;

    std::map<std::string, std::unique_ptr<ns3::AttributeValue> > GetDeviceAttributes() const override;

    std::vector<std::shared_ptr<Node>> &GetNodes() override;
};
}

#endif
