#ifndef QM_YAML_DTO_CONNECTIONYAMLDTO_HPP
#define QM_YAML_DTO_CONNECTIONYAMLDTO_HPP

#include <qm/yaml/dto/Index.hpp>

namespace qm::yaml::dto {
struct Connection: public IdentifiableDTO, public BaseYamlDTO<std::shared_ptr<qm::models::Connection>> {
    std::vector <YamlReference> TargetsRefs;
    qm::models::ConnectionType type;
    std::shared_ptr <qm::models::PointToPointConnection> p2p;

    std::shared_ptr <qm::models::Connection> GetModel() const override;

    const std::string &GetId() const override;

    void SetId(std::string id) override;
};
}

#endif //QM_YAML_DTO_CONNECTIONYAMLDTO_HPP
