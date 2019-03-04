#ifndef QM_YAML_PARSERS_NODE_H_
#define QM_YAML_PARSERS_NODE_H_

#include <yaml-cpp/yaml.h>
#include <unordered_map>
#include "qm/models.hpp"
#include "qm/parsers.hpp"

namespace YAML {
template<>
struct convert<qm::parsers::yaml::NodeYamlDTO> {
    static Node encode(const qm::parsers::yaml::NodeYamlDTO &);

    static bool decode(const Node &node, qm::parsers::yaml::NodeYamlDTO &);
};

template<>
struct convert<qm::parsers::yaml::IpConfigYamlDTO> {
    static Node encode(const qm::parsers::yaml::IpConfigYamlDTO &);

    static bool decode(const Node &node, qm::parsers::yaml::IpConfigYamlDTO&);
};
}

#endif
