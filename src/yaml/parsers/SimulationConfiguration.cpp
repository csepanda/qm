#include <yaml-cpp/yaml.h>

#include <qm/yaml/parsers/NS3Types.hpp>
#include <qm/yaml/parsers/SimulationConfiguration.hpp>

namespace YAML {

Node convert<qm::models::NetworkStack>::encode(const qm::models::NetworkStack &) {
    throw std::logic_error("YAML encoding of qm::models::NetworkStack is not implemented");
}

Node convert<qm::models::SystemIdMarkerStrategy>::encode(const qm::models::SystemIdMarkerStrategy &) {
    throw std::logic_error("YAML encoding of qm::models::SystemIdMarkerStrategy is not implemented");
}

Node convert<qm::yaml::dto::SimulationConfiguration>::encode(
  const qm::yaml::dto::SimulationConfiguration &) {
    throw std::logic_error("YAML encoding of qm::yaml::dto::SimulationConfiguration is not implemented");
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

bool convert<qm::models::SystemIdMarkerStrategy>::decode(
  const Node &node, qm::models::SystemIdMarkerStrategy &strategy) {
    const auto str = node.as<std::string>();

    if (str == "manual") {
        strategy = qm::models::SystemIdMarkerStrategy::Manual;
    } else if (str == "mcl") {
        strategy = qm::models::SystemIdMarkerStrategy::Mlc;
    } else {
        return false;
    }

    return true;
}

bool convert<qm::yaml::dto::SimulationConfiguration>::decode(
  const Node &node, qm::yaml::dto::SimulationConfiguration &simulationConfiguration) {
    const auto networkStackNode = node["networkStack"];
    const auto stopTimeNode = node["stopTime"];
    const auto mpiNode = node["enableMpi"];
    const auto sidMarkerStrategyNode = node["systemIdMarkerStrategy"];

    if (networkStackNode.IsDefined()) {
        simulationConfiguration.NetworkStack = networkStackNode.as<qm::models::NetworkStack>();
    }

    if (stopTimeNode.IsDefined()) {
        simulationConfiguration.StopTime = stopTimeNode.as<ns3::Time>();
    }

    if (mpiNode.IsDefined()) {
        simulationConfiguration.EnableMpi = mpiNode.as<bool>();
    }

    if (sidMarkerStrategyNode.IsDefined()) {
        simulationConfiguration.SystemIdMarkerStrategy = sidMarkerStrategyNode.as<qm::models::SystemIdMarkerStrategy>();
    }

    return true;
}
}
