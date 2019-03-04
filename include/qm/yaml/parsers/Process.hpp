#ifndef QM_YAML_PARSERS_PROCESS_HPP
#define QM_YAML_PARSERS_PROCESS_HPP

#include <qm/yaml/dto/ProcessYamlDTO.hpp>

namespace YAML {
template<>
struct convert<qm::yaml::dto::ProcessYamlDTO> {
    static Node encode(const qm::yaml::dto::ProcessYamlDTO &);

    static bool decode(const Node &node, qm::yaml::dto::ProcessYamlDTO &);
};
}

#endif //QM_YAML_PARSERS_PROCESS_HPP
