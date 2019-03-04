#ifndef QM_YAML_DTO_NODEYAMLDTO_HPP
#define QM_YAML_DTO_NODEYAMLDTO_HPP

#include <vector>
#include <qm/exceptions.hpp>
#include <qm/models.hpp>
#include <qm/yaml/dto/Index.hpp>

namespace qm::yaml::dto {

struct NodeYamlDTO : public IdentifiableDTO {
    std::shared_ptr <qm::models::Node> Node;
    std::vector <IpConfigYamlDTO> IpConfigs{};

    const std::string &GetId() const override;

    void SetId(std::string id) override;
};
}


#endif //QM_YAML_DTO_NODEYAMLDTO_HPP
