#include <qm/yaml/parsers/SimulationConfiguration.hpp>
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

Node convert<qm::yaml::dto::SimulationConfiguration>::encode(
  const qm::yaml::dto::SimulationConfiguration &) {
    throw std::logic_error("Not implemented");
}

bool convert<qm::yaml::dto::SimulationConfiguration>::decode(
  const Node &node, qm::yaml::dto::SimulationConfiguration &simulationConfigurationYamlDTO) {
    const auto networkStackNode = node["networkStack"];

    if (networkStackNode.IsDefined()) {
        simulationConfigurationYamlDTO.networkStack = networkStackNode.as<qm::models::NetworkStack>();
    }

    return true;
}
}
