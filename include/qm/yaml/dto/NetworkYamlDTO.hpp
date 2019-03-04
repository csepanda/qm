#ifndef QM_YAML_DTO_NETWORKYAMLDTO_HPP
#define QM_YAML_DTO_NETWORKYAMLDTO_HPP

namespace qm::parsers::yaml {
struct NetworkYamlDTO : public BaseYamlDTO<qm::models::Network> {
    std::unordered_map<std::string, NodeYamlDTO> NodesDTO{};
    std::unordered_map<std::string, ConnectionYamlDTO> ConnectionsDTO{};

    qm::models::Network GetModel() const override;

    void ResolveContext();
};


}

#endif //QM_YAML_DTO_NETWORKYAMLDTO_HPP
