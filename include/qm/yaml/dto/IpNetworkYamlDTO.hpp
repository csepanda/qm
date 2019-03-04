#ifndef QM_YAML_DTO_IPNETWORKYAMLDTO_HPP
#define QM_YAML_DTO_IPNETWORKYAMLDTO_HPP

#include <qm/yaml/dto/Index.hpp>

namespace qm::yaml::dto {
struct IPNetworkYamlDTO : public BaseYamlDTO<std::shared_ptr<qm::models::IPNetwork>> {
    qm::models::IPVersion ProtocolVersion{};
    std::shared_ptr<qm::models::IPv4Network> IPv4;
    // std::shared_ptr<qm::models::IPv6Address> IPv6;

    std::shared_ptr<models::IPNetwork> GetModel() const override;
};


}

#endif //QM_YAML_DTO_IPNETWORKYAMLDTO_HPP
