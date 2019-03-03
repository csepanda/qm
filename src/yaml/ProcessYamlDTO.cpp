#include <qm/parsers.hpp>
#include <qm/yaml/ProcessYamlDTO.hpp>

namespace qm::parsers::yaml {
std::shared_ptr<qm::models::Process> ProcessYamlDTO::GetApplication() const {
    if (!NodeReference.Resolved) {
        throw InitializationException("Node reference is not resolved yet!", "Process::GetApplication");
    }

    return std::make_shared<models::Process>(m_node, Binary, StackSize, Arguments, StartAt);
}

void ProcessYamlDTO::ResolveNode(NetworkYamlDTO networkYamlDTO) {
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
static const auto SOURCE = "Parse Process from yaml";
Node convert<qm::parsers::yaml::ProcessYamlDTO>::encode(const qm::parsers::yaml::ProcessYamlDTO &) {
    throw std::logic_error("Not implemented");
}

bool convert<qm::parsers::yaml::ProcessYamlDTO>::decode(const Node &node,
                                                            qm::parsers::yaml::ProcessYamlDTO &processYamlDTO) {
    const auto binaryNode = node["binary"];
    const auto argumentsNode = node["arguments"];
    const auto stackSizeNode = node["stackSize"];
    const auto nodeReferenceNode = node["node"];
    const auto startAtNode = node["startAt"];

    if (!(binaryNode.IsDefined() && binaryNode.IsScalar())) {
        throw qm::parsers::ParseException("'binary' is required for Process", SOURCE);
    } else if (!nodeReferenceNode.IsDefined()) {
        throw qm::parsers::ParseException("'node' is required for Process", SOURCE);
    }

    processYamlDTO.Binary = binaryNode.as<std::string>();
    processYamlDTO.NodeReference = nodeReferenceNode.as<qm::parsers::yaml::YamlReference>();

    if (argumentsNode.IsDefined()) {
        if (!argumentsNode.IsSequence()) {
            throw qm::parsers::ParseException("'arguments' should be an array", SOURCE);
        }

        processYamlDTO.Arguments = argumentsNode.as<std::vector<std::string>>();
    }

    if (startAtNode.IsDefined()) {
        if (!startAtNode.IsScalar()) {
            throw qm::parsers::ParseException("'arguments' should be a string", SOURCE);
        }

        processYamlDTO.StartAt = startAtNode.as<ns3::Time>();

    }

    processYamlDTO.StackSize = stackSizeNode.as<uint32_t>(1 << 20);

    return true;
}
}
