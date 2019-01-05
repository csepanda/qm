#include <array>
#include <cstdint>
#include <stdexcept>
#include <string>

namespace qm::models {
class    Node {
};

class IPAddress {
public:
    virtual std::string GetAddressStr() const = 0;
};

class IPNetwork {
public:
    virtual const IPAddress* GetRawAddress() const = 0;
    virtual const IPAddress* GetRawNetmask() const = 0;
    virtual uint32_t GetNetmaskPrefixLength() const = 0;

    virtual std::string GetAddressWithMaskStr() const = 0;
    virtual uint32_t GetCidrMask() const = 0;

    virtual std::string GetNetworkStr() const = 0;
};


const std::string IPv4_VERSION = "IPv4";

class IPv4Address : public IPAddress {
public:
    void SetAddress(std::array<uint8_t, 4> address);

    std::string GetAddressStr() const override;
    std::string GetProtocolVersion() const { return IPv4_VERSION; }

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

    std::string GetProtocolVersion() const { return IPv4_VERSION; }

private:
    IPv4Address m_address;
    uint32_t m_cidr_mask;
};
}
