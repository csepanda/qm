#include <qm/yaml/dto/NodeYamlDTO.hpp>

namespace qm::yaml::dto {

const std::string &NodeYamlDTO::GetId() const {
    if (Node == nullptr) {
        throw qm::UninitializedException("Node is not initialized");
    }

    return Node->GetId();
}

void NodeYamlDTO::SetId(std::string id) {
    if (Node == nullptr) {
        throw qm::UninitializedException("Node is not initialized");
    }

    Node->SetId(id);
}
}
