#include <array>
#include <cstdint>
#include <stdexcept>
#include <string>

namespace qm::models {
class    Node {
};

class IPAddress {
public:
    virtual uint64_t GetRaw() = 0;
    virtual std::string GetAddressStr() = 0;
};

class IPNetwork {
public:
    virtual IPAddress* GetRawAddress() = 0;
    virtual IPAddress* GetRawNetmask() = 0;
    virtual uint32_t  GetNetmaskPrefixLength() = 0;

    virtual std::string GetAddressStr() = 0;
    virtual std::string GetNetmaskStr() = 0;
    virtual std::string GetAddressWithMaskStr() = 0;
};


const std::string IPv4_VERSION = "IPv4";

class IPv4Address : public IPAddress {
public:
    IPv4Address(const std::string& address);
    IPv4Address(const uint32_t raw);

    uint64_t GetRaw() override;
    std::string GetAddressStr() override;

    std::string GetProtocolVersion() const { return IPv4_VERSION; }

private:
    std::array<uint8_t, 4> m_address;
};

class IPv4Network : public IPNetwork {
public:
    IPv4Network(const std::string& address, const std::string& mask);

    IPAddress* GetRawAddress() override;
    IPAddress* GetRawNetmask() override;
    uint32_t  GetNetmaskPrefixLength() override;

    std::string GetAddressStr() override;
    std::string GetNetmaskStr() override;
    std::string GetAddressWithMaskStr() override;

    std::string GetProtocolVersion() const { return IPv4_VERSION; }

private:
    IPv4Address m_address;
    IPv4Address m_mask;
};

struct IPv4FormatException : public std::runtime_error {
    const std::string m_source;

    explicit IPv4FormatException(std::string message, std::string source) :
        std::runtime_error(std::move(message)),
        m_source(std::move(source)) {
    }
};

struct IPv4AddressFormatException : public IPv4FormatException {
    using IPv4FormatException::IPv4FormatException;
};

struct IPv4NetmaskFormatException : public IPv4FormatException {
    using IPv4FormatException::IPv4FormatException;
};
}
