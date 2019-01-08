#ifndef QM_PARSERS_H_
#define QM_PARSERS_H_

#include <array>
#include <cstdint>
#include "model.hpp"

namespace qm::parsers {
namespace yaml {
struct IPAddressYamlDTO {
    qm::models::IPVersion ProtocolVersion {};
    qm::models::IPv4Address IPv4;
    //qm::models::IPv6Address IPv6;
};

struct ConnectionYamlDTO {
    qm::models::ConnectionType type;
    qm::models::PointToPointConnection p2p;
};
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
