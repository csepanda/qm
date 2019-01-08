#pragma once

#include <memory>
#include <array>
#include <map>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <ns3/attribute.h>
#include <ns3/data-rate.h>
#include <ns3/uinteger.h>

namespace qm::models {
class Node {
};

enum class ConnectionType {
    P2P
};

class Connection {
public:
    virtual ConnectionType GetConnectionType() const = 0;
    virtual std::map<std::string, std::unique_ptr<ns3::AttributeValue> > GetChannelAttributes() const = 0;
    virtual std::map<std::string, std::unique_ptr<ns3::AttributeValue> > GetDeviceAttributes() const = 0;
};

class PointToPointConnection : public Connection {
private:
    ns3::UintegerValue m_mtu{};
    ns3::DataRateValue m_dataRate{};
    ns3::TimeValue m_delay{};
public:
    PointToPointConnection() = default;
    void setMtu(uint16_t t_mtu);
    void setDataRate(std::string t_dataRate);
    void setDelay(std::string t_delay);

    ConnectionType GetConnectionType() const override { return ConnectionType::P2P; };
    std::map<std::string, std::unique_ptr<ns3::AttributeValue> > GetChannelAttributes() const override;
    std::map<std::string, std::unique_ptr<ns3::AttributeValue> > GetDeviceAttributes() const override;
};


enum IPVersion {
    IPv4,
    IPv6
};

class IPAddress {
public:
    virtual std::string GetAddressStr() const = 0;
    virtual IPVersion GetProtocolVersion() const = 0;
};

class IPNetwork {
public:
    virtual const IPAddress* GetRawAddress() const = 0;
    virtual const IPAddress* GetRawNetmask() const = 0;
    virtual uint32_t GetNetmaskPrefixLength() const = 0;

    virtual std::string GetAddressWithMaskStr() const = 0;
    virtual uint32_t GetCidrMask() const = 0;

    virtual std::string GetNetworkStr() const = 0;

    virtual IPVersion GetProtocolVersion() const = 0;
};

class IPv4Address : public IPAddress {
public:
    IPv4Address();

    void SetAddress(std::array<uint8_t, 4> address);

    std::string GetAddressStr() const override;
    IPVersion GetProtocolVersion() const override { return IPv4; }

private:
    std::array<uint8_t, 4> m_address;
};

class IPv4Network : public IPNetwork {
public:
    void SetAddress(std::array<uint8_t, 4> address);
    void SetCIDRMask(uint32_t cidr);

    const IPAddress* GetRawAddress() const override;
    uint32_t GetCidrMask() const override;

    std::string GetNetworkStr() const override;

    IPVersion GetProtocolVersion() const override { return IPv4; }

private:
    IPv4Address m_address;
    uint32_t m_cidr_mask;
};
}
