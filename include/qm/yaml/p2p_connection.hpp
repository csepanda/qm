#ifndef QM_PARSERS_P2P_H_
#define QM_PARSERS_P2P_H_

#include <yaml-cpp/yaml.h>
#include <unordered_map>
#include "../model.hpp"
#include "../parsers.hpp"

namespace YAML {
template<>
struct convert<qm::parsers::yaml::ConnectionYamlDTO> {
    static Node encode(const qm::parsers::yaml::ConnectionYamlDTO &connectionDTO);

    static bool decode(const Node &node, qm::parsers::yaml::ConnectionYamlDTO &connectionDTO);
};
}

#endif
