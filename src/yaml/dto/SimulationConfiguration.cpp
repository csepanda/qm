
#include <qm/yaml/dto/SimulationConfiguration.hpp>

qm::models::SimulationConfiguration qm::yaml::dto::SimulationConfiguration::GetModel() const {
    return qm::models::SimulationConfiguration{NetworkStack, StopTime, EnableMpi};
}

