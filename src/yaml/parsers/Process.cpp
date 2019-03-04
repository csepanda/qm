#include <qm/parsers.hpp>
#include <qm/yaml/dto/Process.hpp>
#include <qm/yaml/parsers/Process.hpp>

namespace YAML {
static const auto SOURCE = "Parse Process from yaml";
Node convert<qm::yaml::dto::Process>::encode(const qm::yaml::dto::Process &) {
    throw std::logic_error("Not implemented");
}

bool convert<qm::yaml::dto::Process>::decode(const Node &node,
                                                        qm::yaml::dto::Process &processYamlDTO) {
    const auto binaryNode = node["binary"];
    const auto argumentsNode = node["arguments"];
    const auto stackSizeNode = node["stackSize"];
    const auto nodeReferenceNode = node["node"];
    const auto startAtNode = node["startAt"];

    if (!(binaryNode.IsDefined() && binaryNode.IsScalar())) {
        throw qm::ParseException("'binary' is required for Process", SOURCE);
    } else if (!nodeReferenceNode.IsDefined()) {
        throw qm::ParseException("'node' is required for Process", SOURCE);
    }

    processYamlDTO.Binary = binaryNode.as<std::string>();
    processYamlDTO.NodeReference = nodeReferenceNode.as<qm::yaml::dto::YamlReference>();

    if (argumentsNode.IsDefined()) {
        if (!argumentsNode.IsSequence()) {
            throw qm::ParseException("'arguments' should be an array", SOURCE);
        }

        processYamlDTO.Arguments = argumentsNode.as<std::vector<std::string>>();
    }

    if (startAtNode.IsDefined()) {
        if (!startAtNode.IsScalar()) {
            throw qm::ParseException("'arguments' should be a string", SOURCE);
        }

        processYamlDTO.StartAt = startAtNode.as<ns3::Time>();

    }

    processYamlDTO.StackSize = stackSizeNode.as<uint32_t>(1 << 20);

    return true;
}
}
