#ifndef QM_PARSERS_IP_H_
#define QM_PARSERS_IP_H_
#include <yaml-cpp/yaml.h>
#include "../model.hpp"
#include "../parsers.hpp"

namespace YAML {
template<>
struct convert<qm::parsers::yaml::IPAddressYamlDTO> {
    static Node encode(const qm::parsers::yaml::IPAddressYamlDTO &addressDto);

    static bool decode(const Node &node, qm::parsers::yaml::IPAddressYamlDTO &addressDto);
};
}

#endif
