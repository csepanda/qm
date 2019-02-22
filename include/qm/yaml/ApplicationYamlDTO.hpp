//
// Created by cspanda on 2/22/19.
//

#ifndef QM_YAML_APPLICATIONYAMLDTO_H
#define QM_YAML_APPLICATIONYAMLDTO_H

#include <string>
#include <vector>
#include "dto.h"

namespace qm::parsers::yaml {
struct ApplicationYamlDTO {
    std::string Binary;
    std::vector <std::string> Arguments;
    uint32_t StackSize;
    YamlReference NodeReference;

    std::shared_ptr <qm::models::Application> GetApplication() const;

    void ResolveNode(NetworkYamlDTO networkYamlDTO);

private:
    std::shared_ptr <qm::models::Node> m_node;
};
}

namespace YAML {
template<>
struct convert<qm::parsers::yaml::ApplicationYamlDTO> {
    static Node encode(const qm::parsers::yaml::ApplicationYamlDTO &);

    static bool decode(const Node &node, qm::parsers::yaml::ApplicationYamlDTO &);
};
}

#endif //QM_YAML_APPLICATIONYAMLDTO_H
