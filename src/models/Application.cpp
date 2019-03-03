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

Application::Application(
  std::shared_ptr<Node> m_node,
  std::string m_binary,
  uint32_t m_stackSize,
  std::vector<std::string> m_arguments
)
  : m_node(std::move(m_node)),
    m_binary(std::move(m_binary)),
    m_arguments(std::move(m_arguments)),
    m_stackSize(m_stackSize) {

}
}
