#include <regex>

#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include <qm/parsers/IpUtils.hpp>
#include <qm/parsers.hpp>

namespace YAML {
Node convert<qm::yaml::dto::IPNetworkYamlDTO>::encode(const qm::yaml::dto::IPNetworkYamlDTO &networkYamlDTO) {
    throw std::logic_error("Not implemented");
}

bool convert<qm::yaml::dto::IPNetworkYamlDTO>::decode(const Node &node,
                                                          qm::yaml::dto::IPNetworkYamlDTO &networkYamlDTO) {
    const auto inputNetwork = node.as<std::string>();
    std::vector<std::string> splitted;

    boost::split(splitted, inputNetwork, [](char c) { return c == '/'; });

    if (splitted.size() != 2) {
        throw qm::ParseException("Network doesn't match format 'IPAddress/CidrMask'", inputNetwork);
    }

    const auto inputAddress = splitted[0];
    const auto cidrMask = splitted[1];

    const auto mask = qm::parsers::IpUtils::parseCIDR(cidrMask);
    const auto protocolVersion = qm::parsers::IpUtils::determineIPVersion(inputAddress);

    networkYamlDTO.ProtocolVersion = protocolVersion;
    switch (protocolVersion) {
        case qm::models::IPv4: {
            const auto ipv4Data = qm::parsers::IpUtils::parseIPv4(inputAddress);

            networkYamlDTO.IPv4 = std::make_shared<qm::models::IPv4Network>();
            networkYamlDTO.IPv4->SetAddress(ipv4Data);
            networkYamlDTO.IPv4->SetCIDRMask(mask);
            break;
        }
        case qm::models::IPv6:
            throw std::logic_error("Not implemented");
    }

    return true;
}
}
