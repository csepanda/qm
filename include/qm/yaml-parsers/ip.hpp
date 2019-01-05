#ifndef QM_PARSERS_IP_H_
#define QM_PARSERS_IP_H_
#include <yaml-cpp/yaml.h>
#include "../model.hpp"
#include "../parsers.hpp"

namespace YAML {
template<>
struct convert<qm::parsers::yaml::IPAddressYamlDTO> {
    static Node encode(const qm::parsers::yaml::IPAddressYamlDTO &addressDto) {
        Node node;

        switch (addressDto.ProtocolVersion) {
            case qm::models::IPv4:
                node = addressDto.IPv4.GetAddressStr();
                break;
            case qm::models::IPv6:
                throw std::logic_error("Not implemented");
        }

        return node;
    }

    static bool decode(const Node &node, qm::parsers::yaml::IPAddressYamlDTO& addressDto) {
        const auto inputAddress = node.as<std::string>();
        const auto protocolVersion = qm::parsers::determineIPVersion(inputAddress);

        addressDto.ProtocolVersion = protocolVersion;
        switch (protocolVersion) {
            case qm::models::IPv4: {
                const auto ipv4Data = qm::parsers::parseIPv4(inputAddress);
                addressDto.IPv4.SetAddress(ipv4Data);
                break;
            }
            case qm::models::IPv6:
                throw std::logic_error("Not implemented");
        }

        return true;
    }
};
}

#endif
