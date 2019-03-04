#ifndef QM_YAML_PARSERS_NETWORK_HPP
#define QM_YAML_PARSERS_NETWORK_HPP

#include <yaml-cpp/node/node.h>
#include <qm/parsers.hpp>

namespace YAML {
template<>
struct convert<qm::parsers::yaml::NetworkYamlDTO> {
    static Node encode(const qm::parsers::yaml::NetworkYamlDTO &);

    static bool decode(const Node &node, qm::parsers::yaml::NetworkYamlDTO &);
};

}

#endif //QM_NETWORK_HPP
