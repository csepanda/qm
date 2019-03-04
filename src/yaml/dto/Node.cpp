#include <qm/yaml/dto/Node.hpp>

namespace qm::yaml::dto {

const std::string &Node::GetId() const {
    if (Node == nullptr) {
        throw qm::UninitializedException("Node is not initialized");
    }

    return Node->GetId();
}

void Node::SetId(std::string id) {
    if (Node == nullptr) {
        throw qm::UninitializedException("Node is not initialized");
    }

    Node->SetId(id);
}
}
