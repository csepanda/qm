#pragma once

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

namespace qm::models {

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
    virtual const uint32_t GetCidrMask() const = 0;

    virtual std::string GetNetworkStr() const = 0;

    virtual IPVersion GetProtocolVersion() const = 0;
};

class IPv4Address : public IPAddress {
public:
    IPv4Address() = default;

    void SetAddress(std::array<uint8_t, 4> address);

    std::string GetAddressStr() const override;
    IPVersion GetProtocolVersion() const override { return IPv4; }

private:
    std::array<uint8_t, 4> m_address {};
};

class IPv4Network : public IPNetwork {
public:
    IPv4Network() = default;

    void SetAddress(std::array<uint8_t, 4> address);
    void SetCIDRMask(uint32_t cidr);

    const IPAddress* GetRawAddress() const override;
    const uint32_t GetCidrMask() const override;

    std::string GetNetworkStr() const override;

    IPVersion GetProtocolVersion() const override { return IPv4; }


private:
    IPv4Address m_address {};
    uint32_t m_cidr_mask {};
};

struct foo {
    IPv4Network bar;
};
}
