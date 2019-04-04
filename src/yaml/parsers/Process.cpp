#include <regex>

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
    if (node.IsScalar()) {
        const auto &inlineProcess = node.as<std::string>();

        std::smatch m{};
        if (!std::regex_match(inlineProcess, m, std::regex(R"(^\s?(\w+)\s+([^\s]+)\s+(.*)$)"))) {
            throw qm::ParseException(
              "Format doesn't matched: $NAME_NAME $BINARY $ARGUMENTS. Got: " + inlineProcess,
              "Process parsing"
            );
        }

        const auto nodeId = m[1].str();
        const auto binary = m[2].str();
        const auto args = m[3].str();

        processYamlDTO.NodeReference.Id = nodeId;
        processYamlDTO.NodeReference.Resolved = false;
        processYamlDTO.Binary = binary;
        processYamlDTO.Arguments.push_back(args);
    } else if  (node.IsMap()) {
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
            if (argumentsNode.IsScalar()) {
                processYamlDTO.Arguments.push_back(argumentsNode.as<std::string>());
            } else {
                if (!argumentsNode.IsSequence()) {
                    throw qm::ParseException("'arguments' should be an array", SOURCE);
                }

                processYamlDTO.Arguments = argumentsNode.as<std::vector<std::string>>();
            }
        }

        if (startAtNode.IsDefined()) {
            if (!startAtNode.IsScalar()) {
                throw qm::ParseException("'arguments' should be a string", SOURCE);
            }

            processYamlDTO.StartAt = startAtNode.as<ns3::Time>();

        }

        processYamlDTO.StackSize = stackSizeNode.as<uint32_t>(1 << 20);
    } else {
        throw qm::ParseException("Cannot parse process - Illegal YAML", "Process parsing");
    }

    return true;
}
}
