#include <qm/yaml/parsers/SimulationConfigurationYamlParser.hpp>
#include <yaml-cpp/yaml.h>

namespace YAML {

Node convert<qm::models::NetworkStack>::encode(const qm::models::NetworkStack &) {
    throw std::logic_error("Not implemented");
}

bool convert<qm::models::NetworkStack>::decode(const Node &node, qm::models::NetworkStack &stack) {
    const auto str = node.as<std::string>();

    if (str == "linux") {
        stack = qm::models::NetworkStack::LinuxKernel;
        return true;
    } else if (str == "ns3") {
        stack = qm::models::NetworkStack::Ns3;
        return true;
    }

    return false;
}

Node convert<qm::parsers::yaml::SimulationConfigurationYamlDTO>::encode(
  const qm::parsers::yaml::SimulationConfigurationYamlDTO &) {
    throw std::logic_error("Not implemented");
}

bool convert<qm::parsers::yaml::SimulationConfigurationYamlDTO>::decode(
  const Node &node, qm::parsers::yaml::SimulationConfigurationYamlDTO &simulationConfigurationYamlDTO) {
    const auto networkStackNode = node["networkStack"];

    if (networkStackNode.IsDefined()) {
        simulationConfigurationYamlDTO.networkStack = networkStackNode.as<qm::models::NetworkStack>();
    }

    return true;
}
}
