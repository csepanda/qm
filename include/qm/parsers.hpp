#ifndef QM_PARSERS_H_
#define QM_PARSERS_H_

#include <array>
#include <cstdint>
#include <unordered_map>
#include "model.hpp"

namespace qm::parsers {
namespace yaml {
struct YamlReference {
    std::string Id;
    bool Resolved;
};

struct IPAddressYamlDTO {
    qm::models::IPVersion ProtocolVersion {};
    qm::models::IPv4Address IPv4;
    //qm::models::IPv6Address IPv6;
};

struct IpConfigYamlDTO {
    YamlReference ConnectionRef;
    qm::models::IpConfig IpConfig;
};

struct ConnectionYamlDTO {
    std::vector<YamlReference> TargetsRefs;
    qm::models::ConnectionType type;
    std::shared_ptr<qm::models::PointToPointConnection> p2p;

    std::shared_ptr<qm::models::Connection> GetConnection() {
        switch (type) {
            case models::ConnectionType::P2P:
                return p2p;
        }
    }
};

struct NodeYamlDTO {
    std::shared_ptr<qm::models::Node> Node;
    std::vector<IpConfigYamlDTO> IpConfigs {};
};


struct YamlContextDTO {
    std::unordered_map<std::string, NodeYamlDTO> NodesDTO{};
    std::unordered_map<std::string, ConnectionYamlDTO> ConnectionsDTO{};

    void ResolveContext();
};

YamlReference parseYamlReference(const std::string& reference);
}

qm::models::IPVersion determineIPVersion(const std::string &address);
std::array<uint8_t, 4> parseIPv4(const std::string& address);
std::array<uint8_t, 16> parseIPv6(const std::string& address);

uint32_t parseCIDR(const std::string& cidr);

struct ParseException : public std::runtime_error {
    const std::string m_source;

    explicit ParseException(const std::string &message, std::string source) :
            std::runtime_error(message),
            m_source(std::move(source)) {
    }
};
}

#endif
#include "yaml-parsers/ip.hpp"
#include "yaml-parsers/p2p_connection.hpp"
