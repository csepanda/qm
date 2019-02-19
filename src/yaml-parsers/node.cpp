#include <qm/parsers.hpp>
#include <unordered_map>
#include <qm/yaml-parsers/node.hpp>

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

bool convert<qm::parsers::yaml::IpConfigYamlDTO>::decode(const Node &node, qm::parsers::yaml::IpConfigYamlDTO &) {
    const auto addressYaml = node["address"];
    const auto connectionYaml = node["connection"];

    if (!addressYaml.IsDefined()) {
        throw qm::parsers::ParseException("IpConfig require address fields", node.as<std::string>());
    }

    if (!connectionYaml.IsDefined()) {
        throw qm::parsers::ParseException("IpConfig require connection reference", node.as<std::string>());
    }

    const auto address = addressYaml.as<qm::parsers::yaml::IPNetworkYamlDTO>();
    const auto connection = connectionYaml.as<qm::parsers::yaml::YamlReference>();
    return false;
}
}

