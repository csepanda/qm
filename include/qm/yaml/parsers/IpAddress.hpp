#ifndef QM_YAML_PARSERS_IPADDRESS_HPP
#define QM_YAML_PARSERS_IPADDRESS_HPP

#include <yaml-cpp/yaml.h>
#include <qm/yaml/dto/IpAddressYamlDTO.hpp>

namespace YAML {
template<>
struct convert<qm::parsers::yaml::IPAddressYamlDTO> {
    static Node encode(const qm::parsers::yaml::IPAddressYamlDTO &addressDto);

    static bool decode(const Node &node, qm::parsers::yaml::IPAddressYamlDTO &addressDto);
};
}

#endif //QM_YAML_PARSERS_IPADRESS_HPP
