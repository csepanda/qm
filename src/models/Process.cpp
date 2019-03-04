#include <utility>

#include <qm/models.hpp>

namespace qm::models {
const std::shared_ptr<Node> &Process::GetNode() const {
    return m_node;
}

const std::vector<std::string> &Process::GetArguments() const {
    return m_arguments;
}

const std::string &Process::GetBinary() const {
    return m_binary;
}

uint32_t Process::GetStackSize() const {
    return m_stackSize;
}

Process::Process(
  std::shared_ptr<Node> m_node,
  std::string m_binary,
  uint32_t m_stackSize,
  std::vector<std::string> m_arguments,
  ns3::Time m_startAt
)
  : m_node(std::move(m_node)),
    m_binary(std::move(m_binary)),
    m_arguments(std::move(m_arguments)),
    m_stackSize(m_stackSize),
    m_startAt(std::move(m_startAt)) {

}

const ns3::Time &Process::GetStartTime() const {
    return m_startAt;
}
}
