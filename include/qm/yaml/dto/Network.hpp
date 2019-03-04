#ifndef QM_YAML_DTO_NETWORKYAMLDTO_HPP
#define QM_YAML_DTO_NETWORKYAMLDTO_HPP

namespace qm::yaml::dto {
struct Network: public BaseYamlDTO<qm::models::Network> {
    std::unordered_map<std::string, Node> NodesDTO{};
    std::unordered_map<std::string, Connection> ConnectionsDTO{};

    qm::models::Network GetModel() const override;

    void ResolveContext();
};


}

#endif //QM_YAML_DTO_NETWORKYAMLDTO_HPP
