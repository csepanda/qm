#ifndef QM_YAML_PARSERS_PROCESS_HPP
#define QM_YAML_PARSERS_PROCESS_HPP

#include <qm/yaml/dto/ProcessYamlDTO.hpp>

namespace YAML {
template<>
struct convert<qm::parsers::yaml::ProcessYamlDTO> {
    static Node encode(const qm::parsers::yaml::ProcessYamlDTO &);

    static bool decode(const Node &node, qm::parsers::yaml::ProcessYamlDTO &);
};
}

#endif //QM_YAML_PARSERS_PROCESS_HPP
