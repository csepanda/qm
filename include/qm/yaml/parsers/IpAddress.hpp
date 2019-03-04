#ifndef QM_YAML_PARSERS_IPADDRESS_HPP
#define QM_YAML_PARSERS_IPADDRESS_HPP

#include <yaml-cpp/yaml.h>
#include <qm/yaml/dto/IpAddressYamlDTO.hpp>

namespace YAML {
template<>
struct convert<qm::yaml::dto::IPAddressYamlDTO> {
    static Node encode(const qm::yaml::dto::IPAddressYamlDTO &addressDto);

    static bool decode(const Node &node, qm::yaml::dto::IPAddressYamlDTO &addressDto);
};
}

#endif //QM_YAML_PARSERS_IPADRESS_HPP
