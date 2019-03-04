#ifndef QM_YAML_DTO_IPADDRESSYAMLDTO_HPP
#define QM_YAML_DTO_IPADDRESSYAMLDTO_HPP

#include <qm/models.hpp>

namespace qm::yaml::dto {
struct IPAddressYamlDTO {
    qm::models::IPVersion ProtocolVersion{};
    qm::models::IPv4Address IPv4;
    //qm::models::IPv6Address IPv6;
};
}


#endif //QM_YAML_DTO_IPADDRESSYAMLDTO_HPP
