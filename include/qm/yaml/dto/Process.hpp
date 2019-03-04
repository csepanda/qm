//
// Created by cspanda on 2/22/19.
//

#ifndef QM_YAML_DTO_APPLICATIONYAMLDTO_H
#define QM_YAML_DTO_APPLICATIONYAMLDTO_H

#include <string>
#include <vector>

#include "Index.hpp"
#include "Network.hpp"

namespace qm::yaml::dto {
struct Process : public BaseYamlDTO<std::shared_ptr<qm::models::Process>> {
    std::string Binary;
    std::vector <std::string> Arguments;
    uint32_t StackSize;
    ns3::Time StartAt;
    YamlReference NodeReference;

    std::shared_ptr <qm::models::Process> GetModel() const override;

    void ResolveNode(Network &networkYamlDTO);

private:
    std::shared_ptr <qm::models::Node> m_node;
};
}

#endif //QM_YAML_DTO_APPLICATIONYAMLDTO_H
