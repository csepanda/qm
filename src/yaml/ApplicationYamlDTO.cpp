#include <qm/parsers.hpp>
#include <qm/yaml/ApplicationYamlDTO.hpp>

namespace qm::parsers::yaml {
std::shared_ptr<qm::models::Application> ApplicationYamlDTO::GetApplication() const {
    if (!NodeReference.Resolved) {
        throw InitializationException("Node reference is not resolved yet!", "Application::GetApplication");
    }

    return std::make_shared<models::Application>(m_node, Binary, StackSize, Arguments);
}

void ApplicationYamlDTO::ResolveNode(NetworkYamlDTO networkYamlDTO) {
    if (NodeReference.Resolved) {
        return;
    }

    try {
        m_node = networkYamlDTO.NodesDTO.at(NodeReference.Id).Node;
        NodeReference.Resolved = true;
    } catch (std::out_of_range &err) {
        std::stringstream ss;
        ss << "Cannot resolve node with id '" << NodeReference.Id << "'";

        auto message = std::move(ss.str());
        ss.str(std::string());
        ss << "for an application";
        auto source = std::move(ss.str());

        throw ParseException(message, std::move(source));
    }
}
}

namespace YAML {
static const auto SOURCE = "Parse Application from yaml";
Node convert<qm::parsers::yaml::ApplicationYamlDTO>::encode(const qm::parsers::yaml::ApplicationYamlDTO &) {
    throw std::logic_error("Not implemented");
}

bool convert<qm::parsers::yaml::ApplicationYamlDTO>::decode(const Node &node,
                                                            qm::parsers::yaml::ApplicationYamlDTO &applicationDTO) {
    const auto binaryNode = node["binary"];
    const auto argumentsNode = node["arguments"];
    const auto stackSizeNode = node["stackSize"];
    const auto nodeReferenceNode = node["node"];

    if (!(binaryNode.IsDefined() && binaryNode.IsScalar())) {
        throw qm::parsers::ParseException("'binary' is required for Application", SOURCE);
    } else if (!nodeReferenceNode.IsDefined()) {
        throw qm::parsers::ParseException("'node is required for Application", SOURCE);
    }

    applicationDTO.Binary = binaryNode.as<std::string>();
    applicationDTO.NodeReference = nodeReferenceNode.as<qm::parsers::yaml::YamlReference>();

    if (argumentsNode.IsDefined()) {
        if (!argumentsNode.IsSequence()) {
            throw qm::parsers::ParseException("'arguments' should be an array", SOURCE);
        }

        applicationDTO.Arguments = argumentsNode.as<std::vector<std::string>>();
    }

    applicationDTO.StackSize = stackSizeNode.as<uint32_t>(1 << 20);

    return true;
}
}
