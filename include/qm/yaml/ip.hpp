#ifndef QM_PARSERS_IP_H_
#define QM_PARSERS_IP_H_

#include <yaml-cpp/yaml.h>
#include "../model.hpp"
#include "../parsers.hpp"

namespace qm::parsers {
qm::models::IPVersion determineIPVersion(const std::string &address);

std::array<uint8_t, 4> parseIPv4(const std::string &address);

std::array<uint8_t, 16> parseIPv6(const std::string &address);

uint32_t parseCIDR(const std::string &cidr);
}

namespace YAML {
template<>
struct convert<qm::parsers::yaml::IPAddressYamlDTO> {
    static Node encode(const qm::parsers::yaml::IPAddressYamlDTO &addressDto);

    static bool decode(const Node &node, qm::parsers::yaml::IPAddressYamlDTO &addressDto);
};

template<>
struct convert<qm::parsers::yaml::IPNetworkYamlDTO> {
    static Node encode(const qm::parsers::yaml::IPNetworkYamlDTO &networkYamlDTO);

    static bool decode(const Node &node, qm::parsers::yaml::IPNetworkYamlDTO &networkYamlDTO);
};
}

#endif
