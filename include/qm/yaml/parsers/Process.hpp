#ifndef QM_YAML_PARSERS_PROCESS_HPP
#define QM_YAML_PARSERS_PROCESS_HPP

#include <qm/yaml/dto/Process.hpp>

namespace YAML {
template<>
struct convert<qm::yaml::dto::Process> {
    static Node encode(const qm::yaml::dto::Process &);

    static bool decode(const Node &node, qm::yaml::dto::Process &);
};
}

#endif //QM_YAML_PARSERS_PROCESS_HPP
