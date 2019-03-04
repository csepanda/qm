#ifndef QM_YAML_PARSERS_NETWORK_HPP
#define QM_YAML_PARSERS_NETWORK_HPP

#include <yaml-cpp/node/node.h>
#include <qm/parsers.hpp>

namespace YAML {
template<>
struct convert<qm::yaml::dto::Network> {
    static Node encode(const qm::yaml::dto::Network &);

    static bool decode(const Node &node, qm::yaml::dto::Network &);
};

}

#endif //QM_NETWORK_HPP
