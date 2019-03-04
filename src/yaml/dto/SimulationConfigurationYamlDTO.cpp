
#include <qm/yaml/dto/SimulationConfigurationYamlDTO.hpp>

qm::models::SimulationConfiguration qm::yaml::dto::SimulationConfigurationYamlDTO::GetModel() const {
    return qm::models::SimulationConfiguration{networkStack};
}

