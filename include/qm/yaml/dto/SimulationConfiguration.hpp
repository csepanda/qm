#ifndef QM_YAML_DTO_SIMULATIONCONFIGURATIONYAMLDTO_H
#define QM_YAML_DTO_SIMULATIONCONFIGURATIONYAMLDTO_H

#include <qm/models.hpp>
#include <qm/yaml/dto/Index.hpp>

namespace qm::yaml::dto {
struct SimulationConfiguration: public BaseYamlDTO<qm::models::SimulationConfiguration> {
    qm::models::SystemIdMarkerStrategy SystemIdMarkerStrategy{};
    qm::models::NetworkStack NetworkStack{};
    ns3::Time StopTime{};
    bool EnableMpi{};

    qm::models::SimulationConfiguration GetModel() const override;
};
}

#endif //QM_YAML_DTO_SIMULATIONCONFIGURATIONYAMLDTO_H
