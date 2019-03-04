#ifndef QM_YAML_PARSERS_IPNETWORK_HPP
#define QM_YAML_PARSERS_IPNETWORK_HPP

#include <yaml-cpp/yaml.h>
#include <qm/yaml/dto/IpNetworkYamlDTO.hpp>

namespace YAML {
template<>
struct convert<qm::parsers::yaml::IPNetworkYamlDTO> {
    static Node encode(const qm::parsers::yaml::IPNetworkYamlDTO &networkYamlDTO);

    static bool decode(const Node &node, qm::parsers::yaml::IPNetworkYamlDTO &networkYamlDTO);
};
}

#endif //QM_YAML_PARSERS_IPNETWORK_HPP
