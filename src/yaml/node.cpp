#include <qm/parsers.hpp>
#include <unordered_map>

namespace YAML {

Node convert<qm::parsers::yaml::NodeYamlDTO>::encode(const qm::parsers::yaml::NodeYamlDTO &nodeYamlDTO) {
    throw std::logic_error("Not implemented");
}

bool convert<qm::parsers::yaml::NodeYamlDTO>::decode(const Node &node,
                                                           qm::parsers::yaml::NodeYamlDTO &nodeYamlDTO) {
    nodeYamlDTO.Node.reset(new qm::models::Node);

    const auto id = node["id"];

    if (id.IsDefined()) {
        nodeYamlDTO.Node->SetId(id.as<std::string>());
    }

    const auto ipConfigs = node["ipConfig"];

    if (ipConfigs.IsDefined()) {
        if (!ipConfigs.IsSequence()) {
            throw qm::parsers::ParseException("ipConfig should be sequence", "Node");
        }

        for (const auto& ipConfigYaml : ipConfigs) {
            const auto ipConfigDTO = ipConfigYaml.as<qm::parsers::yaml::IpConfigYamlDTO>();

            nodeYamlDTO.IpConfigs.push_back(ipConfigDTO);
        }
    }

    return true;
}

Node convert<qm::parsers::yaml::IpConfigYamlDTO>::encode(const qm::parsers::yaml::IpConfigYamlDTO &) {
    throw std::logic_error("Not implemented");
}

bool convert<qm::parsers::yaml::IpConfigYamlDTO>::decode(const Node &node, qm::parsers::yaml::IpConfigYamlDTO &ipConfigYamlDTO) {
    const auto addressYaml = node["address"];
    const auto connectionYaml = node["connection"];

    if (!addressYaml.IsDefined()) {
        throw qm::parsers::ParseException("IpConfig require address fields", node.as<std::string>());
    }

    if (!connectionYaml.IsDefined()) {
        throw qm::parsers::ParseException("IpConfig require connection reference", node.as<std::string>());
    }

    const auto parsedNetwork = addressYaml.as<qm::parsers::yaml::IPNetworkYamlDTO>();
    const auto parsedConnection = connectionYaml.as<qm::parsers::yaml::YamlReference>();

    ipConfigYamlDTO.ConnectionRef = parsedConnection;
    switch (parsedNetwork.ProtocolVersion) {
        case qm::models::IPv4: {
            ipConfigYamlDTO.IpConfig.Address = std::make_shared<qm::models::IPv4Network>(parsedNetwork.IPv4);
            break;
        }
        case qm::models::IPv6: {
            throw std::logic_error("Not implemented");
        }
    }

    return true;
}
}

