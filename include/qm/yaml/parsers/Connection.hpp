#ifndef QM_YAML_PARSERS_CONNECTION_H_
#define QM_YAML_PARSERS_CONNECTION_H_

#include <yaml-cpp/yaml.h>
#include <unordered_map>
#include "qm/models.hpp"
#include "qm/parsers.hpp"

namespace YAML {
template<>
struct convert<qm::yaml::dto::ConnectionYamlDTO> {
    static Node encode(const qm::yaml::dto::ConnectionYamlDTO &connectionDTO);

    static bool decode(const Node &node, qm::yaml::dto::ConnectionYamlDTO &connectionDTO);
};
}

#endif
