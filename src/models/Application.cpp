#include <qm/model.hpp>

namespace qm::models {
const std::shared_ptr<Node> &Application::GetNode() const {
    return m_node;
}

const std::vector<std::string> &Application::GetArguments() const {
    return m_arguments;
}

const std::string &Application::GetBinary() const {
    return m_binary;
}

uint32_t Application::GetStackSize() const {
    return m_stackSize;
}
}
