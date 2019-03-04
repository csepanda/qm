#ifndef QM_YAML_PARSERS_IPNETWORK_HPP
#define QM_YAML_PARSERS_IPNETWORK_HPP

#include <yaml-cpp/yaml.h>
#include <qm/yaml/dto/IpNetwork.hpp>

namespace YAML {
template<>
struct convert<qm::yaml::dto::IPNetwork> {
    static Node encode(const qm::yaml::dto::IPNetwork &networkYamlDTO);

    static bool decode(const Node &node, qm::yaml::dto::IPNetwork &networkYamlDTO);
};
}

#endif //QM_YAML_PARSERS_IPNETWORK_HPP
