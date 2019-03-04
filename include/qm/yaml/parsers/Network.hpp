#ifndef QM_YAML_PARSERS_NETWORK_HPP
#define QM_YAML_PARSERS_NETWORK_HPP

#include <yaml-cpp/node/node.h>
#include <qm/parsers.hpp>

namespace YAML {
template<>
struct convert<qm::yaml::dto::NetworkYamlDTO> {
    static Node encode(const qm::yaml::dto::NetworkYamlDTO &);

    static bool decode(const Node &node, qm::yaml::dto::NetworkYamlDTO &);
};

}

#endif //QM_NETWORK_HPP
