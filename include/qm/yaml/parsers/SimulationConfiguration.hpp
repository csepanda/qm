#ifndef QM_YAML_PARSER_SIMULATIONCONFIGURATIONYAMLPARSER_H
#define QM_YAML_PARSER_SIMULATIONCONFIGURATIONYAMLPARSER_H

#include <qm/yaml/dto/SimulationConfiguration.hpp>
#include <yaml-cpp/yaml.h>

namespace YAML {
template<>
struct convert<qm::models::NetworkStack> {
    static Node encode(const qm::models::NetworkStack &);

    static bool decode(const Node &node, qm::models::NetworkStack &);
};

template <>
struct convert<qm::models::SystemIdMarkerStrategy> {
    static Node encode(const qm::models::SystemIdMarkerStrategy &);

    static bool decode(const Node &node, qm::models::SystemIdMarkerStrategy &);
};

template<>
struct convert<qm::yaml::dto::SimulationConfiguration> {
    static Node encode(const qm::yaml::dto::SimulationConfiguration &);

    static bool decode(const Node &node, qm::yaml::dto::SimulationConfiguration &);
};
}
#endif //QM_YAML_PARSER_SIMULATIONCONFIGURATIONYAMLPARSER_H
