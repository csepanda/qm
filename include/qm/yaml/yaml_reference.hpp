#ifndef QM_YAML_PARSERS_NODE_H_
#define QM_YAML_PARSERS_NODE_H_

#include <qm/parsers.hpp>

namespace YAML {
template<>
struct convert<qm::parsers::yaml::YamlReference> {
    static Node encode(const qm::parsers::yaml::YamlReference &);

    static bool decode(const Node &node, qm::parsers::yaml::YamlReference &);
};

}

#endif
