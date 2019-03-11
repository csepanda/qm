#include <yaml-cpp/yaml.h>

#include <qm/yaml/parsers/NS3Types.hpp>
#include <qm/yaml/parsers/SimulationConfiguration.hpp>

namespace YAML {

Node convert<qm::models::NetworkStack>::encode(const qm::models::NetworkStack &) {
    throw std::logic_error("Not implemented");
}

bool convert<qm::models::NetworkStack>::decode(const Node &node, qm::models::NetworkStack &stack) {
    const auto str = node.as<std::string>();

    if (str == "linux") {
        stack = qm::models::NetworkStack::LinuxKernel;
    } else if (str == "ns3") {
        stack = qm::models::NetworkStack::Ns3;
    } else {
        return false;
    }

    return true;
}

Node convert<qm::yaml::dto::SimulationConfiguration>::encode(
  const qm::yaml::dto::SimulationConfiguration &) {
    throw std::logic_error("Not implemented");
}

bool convert<qm::yaml::dto::SimulationConfiguration>::decode(
  const Node &node, qm::yaml::dto::SimulationConfiguration &simulationConfigurationYamlDTO) {
    const auto networkStackNode = node["networkStack"];
    const auto stopTimeNode = node["stopTime"];

    if (networkStackNode.IsDefined()) {
        simulationConfigurationYamlDTO.NetworkStack = networkStackNode.as<qm::models::NetworkStack>();
    }

    if (stopTimeNode.IsDefined()) {
        simulationConfigurationYamlDTO.StopTime = stopTimeNode.as<ns3::Time>();
    }


    return true;
}
}
