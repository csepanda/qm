#ifndef QM_YAML_PARSERS_IPNETWORK_HPP
#define QM_YAML_PARSERS_IPNETWORK_HPP

#include <yaml-cpp/yaml.h>
#include <qm/yaml/dto/IpNetworkYamlDTO.hpp>

namespace YAML {
template<>
struct convert<qm::yaml::dto::IPNetworkYamlDTO> {
    static Node encode(const qm::yaml::dto::IPNetworkYamlDTO &networkYamlDTO);

    static bool decode(const Node &node, qm::yaml::dto::IPNetworkYamlDTO &networkYamlDTO);
};
}

#endif //QM_YAML_PARSERS_IPNETWORK_HPP
