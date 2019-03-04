#include <qm/parsers/IpUtils.hpp>
#include <qm/yaml/parsers/IpAddress.hpp>

namespace YAML {
Node convert<qm::yaml::dto::IPAddressYamlDTO>::encode(const qm::yaml::dto::IPAddressYamlDTO &addressDto) {
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

bool convert<qm::yaml::dto::IPAddressYamlDTO>::decode(const Node &node,
                                                          qm::yaml::dto::IPAddressYamlDTO &addressDto) {
    const auto inputAddress = node.as<std::string>();
    const auto protocolVersion = qm::parsers::IpUtils::determineIPVersion(inputAddress);

    addressDto.ProtocolVersion = protocolVersion;
    switch (protocolVersion) {
        case qm::models::IPv4: {
            const auto ipv4Data = qm::parsers::IpUtils::parseIPv4(inputAddress);
            addressDto.IPv4.SetAddress(ipv4Data);
            break;
        }
        case qm::models::IPv6:
            throw std::logic_error("Not implemented");
    }

    return true;
}
}

