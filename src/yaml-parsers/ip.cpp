#include <boost/algorithm/string.hpp>

#include <qm/parsers.hpp>
#include <qm/yaml-parsers/ip.hpp>


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

bool convert<qm::parsers::yaml::IPAddressYamlDTO>::decode(const Node &node,
                                                          qm::parsers::yaml::IPAddressYamlDTO &addressDto) {
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

Node convert<qm::parsers::yaml::IPNetworkYamlDTO>::encode(const qm::parsers::yaml::IPNetworkYamlDTO &networkYamlDTO) {
    throw std::logic_error("Not implemented");
}

bool convert<qm::parsers::yaml::IPNetworkYamlDTO>::decode(const Node &node,
                                                          qm::parsers::yaml::IPNetworkYamlDTO &networkYamlDTO) {
    const auto inputNetwork = node.as<std::string>();
    std::vector<std::string> splitted;

    boost::split(splitted, inputNetwork, [](char c){return c == '/';});

    if (splitted.size() != 2) {
        throw qm::parsers::ParseException("Network doesn't match format 'IPAddress/CidrMask'", inputNetwork);
    }

    const auto inputAddress = splitted[0];
    const auto cidrMask = splitted[1];

    const auto mask = qm::parsers::parseCIDR(cidrMask);
    const auto protocolVersion = qm::parsers::determineIPVersion(inputAddress);

    networkYamlDTO.ProtocolVersion = protocolVersion;
    switch (protocolVersion) {
        case qm::models::IPv4: {
            const auto ipv4Data = qm::parsers::parseIPv4(inputAddress);
            networkYamlDTO.IPv4.SetAddress(ipv4Data);
            networkYamlDTO.IPv4.SetCIDRMask(mask);
            break;
        }
        case qm::models::IPv6:
            throw std::logic_error("Not implemented");
    }

    return true;
}

}

