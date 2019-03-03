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
struct convert<qm::parsers::yaml::SimulationConfigurationYamlDTO> {
    static Node encode(const qm::parsers::yaml::SimulationConfigurationYamlDTO &);

    static bool decode(const Node &node, qm::parsers::yaml::SimulationConfigurationYamlDTO &);
};
}
#endif //QM_YAML_PARSER_SIMULATIONCONFIGURATIONYAMLPARSER_H
