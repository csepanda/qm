#ifndef QM_YAML_PARSER_SIMULATIONCONFIGURATIONYAMLPARSER_H
#define QM_YAML_PARSER_SIMULATIONCONFIGURATIONYAMLPARSER_H

#include <qm/yaml/dto/SimulationConfigurationYamlDTO.hpp>
#include <yaml-cpp/yaml.h>

namespace YAML {
template<>
struct convert<qm::models::NetworkStack> {
    static Node encode(const qm::models::NetworkStack &);

    static bool decode(const Node &node, qm::models::NetworkStack &);
};

template<>
struct convert<qm::yaml::dto::SimulationConfigurationYamlDTO> {
    static Node encode(const qm::yaml::dto::SimulationConfigurationYamlDTO &);

    static bool decode(const Node &node, qm::yaml::dto::SimulationConfigurationYamlDTO &);
};
}
#endif //QM_YAML_PARSER_SIMULATIONCONFIGURATIONYAMLPARSER_H
