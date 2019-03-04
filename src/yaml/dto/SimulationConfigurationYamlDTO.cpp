
#include <qm/yaml/dto/SimulationConfigurationYamlDTO.hpp>

qm::models::SimulationConfiguration qm::parsers::yaml::SimulationConfigurationYamlDTO::GetModel() const {
    return qm::models::SimulationConfiguration{networkStack};
}

