#include <qm/parsers.hpp>

namespace YAML {
Node convert<qm::parsers::yaml::IPAddressYamlDTO>::encode(const qm::parsers::yaml::IPAddressYamlDTO &addressDto) {
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

bool convert<qm::parsers::yaml::IPAddressYamlDTO>::decode(const Node &node, qm::parsers::yaml::IPAddressYamlDTO& addressDto) {
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
}

