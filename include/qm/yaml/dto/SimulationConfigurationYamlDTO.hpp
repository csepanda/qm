#ifndef QM_YAML_DTO_SIMULATIONCONFIGURATIONYAMLDTO_H
#define QM_YAML_DTO_SIMULATIONCONFIGURATIONYAMLDTO_H

#include <qm/model.hpp>

namespace qm::parsers::yaml {
struct SimulationConfigurationYamlDTO {
    qm::models::NetworkStack networkStack;
    qm::models::SimulationConfiguration GetModel();
};
}

#endif //QM_YAML_DTO_SIMULATIONCONFIGURATIONYAMLDTO_H
