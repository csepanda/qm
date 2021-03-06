#ifndef QM_YAML_PARSERS_NODE_H_
#define QM_YAML_PARSERS_NODE_H_

#include <yaml-cpp/yaml.h>
#include <unordered_map>
#include "qm/models.hpp"
#include "qm/parsers.hpp"

namespace YAML {
template<>
struct convert<qm::yaml::dto::Node> {
    static Node encode(const qm::yaml::dto::Node &);

    static bool decode(const Node &node, qm::yaml::dto::Node &);
};

template<>
struct convert<qm::yaml::dto::IpConfigYamlDTO> {
    static Node encode(const qm::yaml::dto::IpConfigYamlDTO &);

    static bool decode(const Node &node, qm::yaml::dto::IpConfigYamlDTO&);
};
}

#endif
