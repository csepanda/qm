#include <qm/models/ConfigurationFiles/BgpConfig.hpp>
#include <qm/models/ip.hpp>

namespace qm::models::configurations {
BgpNeighbor::BgpNeighbor(std::string &ipAddress, uint16_t as, bool nextHopSelf, bool activate)
  : IpAddress{ipAddress},
    As{as},
    NextHopSelf{nextHopSelf},
    Activated{activate} {
}

BgpConfig::BgpConfig(const std::string &path, uint16_t as, const std::vector<BgpNeighbor> &neighbors)
  : ConfigurationFile(path),
    m_as{as},
    m_neighbors{neighbors} {

}

uint16_t BgpConfig::GetAsNumber() const {
    return m_as;
}

std::vector<BgpNeighbor> BgpConfig::GetNeighbors() const {
    return m_neighbors;
}

std::unique_ptr<std::istream> BgpConfig::GetStream() const {
    std::unique_ptr<std::stringstream> ss = std::make_unique<std::stringstream>();

    *ss << "hostname bgpd" << std::endl
        << "password zebra" << std::endl
        << "log stdout" << std::endl
        << "router bgp " << m_as << std::endl;

    auto routerIdAddress = models::IPv4Address();

    std::array<uint8_t, 4> rawAddress{};

    rawAddress[0] = static_cast<uint8_t>((m_as >> 24) & 0xFF);
    rawAddress[1] = static_cast<uint8_t>((m_as >> 16) & 0xFF);
    rawAddress[2] = static_cast<uint8_t>((m_as >> 8) & 0xFF);
    rawAddress[3] = static_cast<uint8_t>(m_as & 0xFF);

    routerIdAddress.SetAddress(rawAddress);

    *ss << "bgp router-id " << routerIdAddress.GetAddressStr() << std::endl;

    for (const auto &neighbor : m_neighbors) {
        *ss << "neighbor " << neighbor.IpAddress << " remote-as " << neighbor.As << std::endl;
        *ss << "neighbor " << neighbor.IpAddress << " advertisement-internal " << 5 << std::endl;
    }

    *ss << "redistribute connected" << std::endl;

    *ss << "address-family ipv4 unicast" << std::endl;
    for (const auto &neighbor : m_neighbors) {
        if (neighbor.Activated) {
            *ss << "neighbor " << neighbor.IpAddress << " activate" << std::endl;
        }

        if (neighbor.NextHopSelf) {
            *ss << "neighbor " << neighbor.IpAddress << " next-hop-self" << std::endl;
        }
    }

    *ss << "exit-address-family" << std::endl;

    return ss;
}

ConfigurationFileType BgpConfig::GetType() const {
    return ConfigurationFileType::Bgp;
}
}
