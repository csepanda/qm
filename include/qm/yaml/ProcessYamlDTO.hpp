//
// Created by cspanda on 2/22/19.
//

#ifndef QM_YAML_APPLICATIONYAMLDTO_H
#define QM_YAML_APPLICATIONYAMLDTO_H

#include <string>
#include <vector>
#include "dto.h"

namespace qm::parsers::yaml {
struct ProcessYamlDTO {
    std::string Binary;
    std::vector <std::string> Arguments;
    uint32_t StackSize;
    ns3::Time StartAt;
    YamlReference NodeReference;

    std::shared_ptr <qm::models::Process> GetApplication() const;

    void ResolveNode(NetworkYamlDTO networkYamlDTO);

private:
    std::shared_ptr <qm::models::Node> m_node;
};
}

namespace YAML {
template<>
struct convert<qm::parsers::yaml::ProcessYamlDTO> {
    static Node encode(const qm::parsers::yaml::ProcessYamlDTO &);

    static bool decode(const Node &node, qm::parsers::yaml::ProcessYamlDTO &);
};
}

#endif //QM_YAML_APPLICATIONYAMLDTO_H
