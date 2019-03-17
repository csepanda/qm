#ifndef QM_YAML_DTO_NETWORKYAMLDTO_HPP
#define QM_YAML_DTO_NETWORKYAMLDTO_HPP

namespace qm::yaml::dto {
struct Network: public BaseYamlDTO<qm::models::Network> {
    std::map<std::string, Node> NodesDTO{};
    std::map<std::string, Connection> ConnectionsDTO{};

    qm::models::Network GetModel() const override;

    void ResolveContext();
};


}

#endif //QM_YAML_DTO_NETWORKYAMLDTO_HPP
