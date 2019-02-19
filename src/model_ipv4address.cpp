#include <qm/model.hpp>

#include <array>
#include <boost/tokenizer.hpp>
#include <cmath>
#include <regex>
#include <string>
#include <qm/model/ip.hpp>


namespace qm::models {
void IPv4Address::SetAddress(std::array<uint8_t, 4> address) {
    m_address = address;
}

std::string IPv4Address::GetAddressStr() const {
    std::stringstream ss;

    ss << std::to_string(m_address[0]) << '.';
    ss << std::to_string(m_address[1]) << '.';
    ss << std::to_string(m_address[2]) << '.';
    ss << std::to_string(m_address[3]);

	return ss.str();
}

void IPv4Network::SetAddress(std::array<uint8_t, 4> address) {
    m_address.SetAddress(address);
}

void IPv4Network::SetCIDRMask(uint32_t cidr) {
    if (cidr > 32) {
        throw std::invalid_argument("IPv4 cidr mask cannot be larger than 32, got: " + std::to_string(cidr));
    }

    m_cidr_mask = cidr;
}

const IPAddress* IPv4Network::GetRawAddress() const {
    return &m_address;
}

const uint32_t IPv4Network::GetCidrMask() const {
    return m_cidr_mask;
}

std::string IPv4Network::GetNetworkStr() const {
    std::stringstream ss;

    ss << m_address.GetAddressStr() << "/" << GetCidrMask();
    return ss.str();
}
}
