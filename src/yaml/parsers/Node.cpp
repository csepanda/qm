#include <qm/parsers.hpp>
#include <unordered_map>

namespace YAML {

Node convert<qm::yaml::dto::NodeYamlDTO>::encode(const qm::yaml::dto::NodeYamlDTO &nodeYamlDTO) {
    throw std::logic_error("Not implemented");
}

bool convert<qm::yaml::dto::NodeYamlDTO>::decode(const Node &node,
                                                           qm::yaml::dto::NodeYamlDTO &nodeYamlDTO) {
    nodeYamlDTO.Node.reset(new qm::models::Node);

    const auto id = node["id"];

    if (id.IsDefined()) {
        nodeYamlDTO.Node->SetId(id.as<std::string>());
    }

    const auto ipConfigs = node["ipConfig"];

    if (ipConfigs.IsDefined()) {
        if (!ipConfigs.IsSequence()) {
            throw qm::ParseException("ipConfig should be sequence", "Node");
        }

        for (const auto& ipConfigYaml : ipConfigs) {
            const auto ipConfigDTO = ipConfigYaml.as<qm::yaml::dto::IpConfigYamlDTO>();

            nodeYamlDTO.IpConfigs.push_back(ipConfigDTO);
        }
    }

    return true;
}

Node convert<qm::yaml::dto::IpConfigYamlDTO>::encode(const qm::yaml::dto::IpConfigYamlDTO &) {
    throw std::logic_error("Not implemented");
}

bool convert<qm::yaml::dto::IpConfigYamlDTO>::decode(const Node &node, qm::yaml::dto::IpConfigYamlDTO &ipConfigYamlDTO) {
    const auto addressYaml = node["address"];
    const auto connectionYaml = node["connection"];

    if (!addressYaml.IsDefined()) {
        // TODO remove node.as<std::string> with correct source
        throw qm::ParseException("IpConfig require address fields", node.as<std::string>());
    }

    if (!connectionYaml.IsDefined()) {
        throw qm::ParseException("IpConfig require connection reference", node.as<std::string>());
    }

    const auto parsedNetwork = addressYaml.as<qm::yaml::dto::IPNetworkYamlDTO>();
    const auto parsedConnection = connectionYaml.as<qm::yaml::dto::YamlReference>();

    ipConfigYamlDTO.ConnectionRef = parsedConnection;
    ipConfigYamlDTO.IpConfig = std::make_shared<qm::models::IpConfig>();
    ipConfigYamlDTO.IpConfig->Address = parsedNetwork.GetModel();

    return true;
}
}

