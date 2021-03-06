#include <qm/parsers.hpp>
#include <unordered_map>

namespace YAML {

Node convert<qm::yaml::dto::Node>::encode(const qm::yaml::dto::Node &nodeYamlDTO) {
    throw std::logic_error("Not implemented");
}

bool convert<qm::yaml::dto::Node>::decode(const Node &node,
                                                           qm::yaml::dto::Node &nodeYamlDTO) {
    nodeYamlDTO.Node.reset(new qm::models::Node);

    const auto id = node["id"];
    const auto ipConfigs = node["ipConfig"];
    const auto filesNode = node["files"];
    const auto sidNode = node["systemId"];

    if (id.IsDefined()) {
        nodeYamlDTO.Node->SetId(id.as<std::string>());
    }

    if (sidNode.IsDefined()) {
        nodeYamlDTO.Node->SetSystemId(sidNode.as<uint32_t >());
    }

    if (ipConfigs.IsDefined()) {
        if (!ipConfigs.IsSequence()) {
            throw qm::ParseException("ipConfig should be sequence", "Node");
        }

        for (const auto& ipConfigYaml : ipConfigs) {
            const auto ipConfigDTO = ipConfigYaml.as<qm::yaml::dto::IpConfigYamlDTO>();

            nodeYamlDTO.IpConfigs.push_back(ipConfigDTO);
        }
    }

    if (filesNode.IsDefined()) {
        if (!filesNode.IsSequence()) {
            throw qm::ParseException("files should be a sequence", "Decode node from yaml");
        }

        const auto filesDTO = filesNode.as<std::vector<qm::yaml::dto::File>>();

        for (const auto &fileDTO : filesDTO) {
            nodeYamlDTO.Node->AddFile(fileDTO.GetModel());
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

    const auto parsedNetwork = addressYaml.as<qm::yaml::dto::IPNetwork>();
    const auto parsedConnection = connectionYaml.as<qm::yaml::dto::YamlReference>();

    ipConfigYamlDTO.ConnectionRef = parsedConnection;
    ipConfigYamlDTO.IpConfig = std::make_shared<qm::models::IpConfig>();
    ipConfigYamlDTO.IpConfig->Address = parsedNetwork.GetModel();

    return true;
}
}

