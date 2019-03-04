#ifndef QM_YAML_PARSERS_YAMLREFERENCE_HPP
#define QM_YAML_PARSERS_YAMLREFERENCE_HPP

#include <yaml-cpp/yaml.h>
#include <qm/yaml/dto/Index.hpp>

namespace YAML {
template<>
struct convert<qm::parsers::yaml::YamlReference> {
    static Node encode(const qm::parsers::yaml::YamlReference &);

    static bool decode(const Node &node, qm::parsers::yaml::YamlReference &);
};
}

#endif //QM_YAML_PARSERS_YAMLREFERENCE_HPP
