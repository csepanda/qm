#ifndef QM_YAML_PARSERS_IPADDRESS_HPP
#define QM_YAML_PARSERS_IPADDRESS_HPP

#include <yaml-cpp/yaml.h>
#include <qm/yaml/dto/IpAddress.hpp>

namespace YAML {
template<>
struct convert<qm::yaml::dto::IPAddress> {
    static Node encode(const qm::yaml::dto::IPAddress &addressDto);

    static bool decode(const Node &node, qm::yaml::dto::IPAddress &addressDto);
};
}

#endif //QM_YAML_PARSERS_IPADRESS_HPP
