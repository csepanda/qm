#ifndef QM_MODEL_PROCESS_HPP
#define QM_MODEL_PROCESS_HPP

#include <string>
#include <vector>
#include <utility>
#include "node.hpp"

namespace qm::models {
class Process {
    std::shared_ptr<Node> m_node;
    std::string m_binary;
    std::vector<std::string> m_arguments;
    uint32_t m_stackSize;
    ns3::Time m_startAt;
public:
    Process(
      std::shared_ptr<Node> m_node,
      std::string m_binary,
      uint32_t m_stackSize,
      std::vector<std::string> m_arguments,
      ns3::Time m_startAt
    );

    const std::shared_ptr<Node> &GetNode() const;

    const std::string &GetBinary() const;

    const std::vector<std::string> &GetArguments() const;

    const ns3::Time &GetStartTime() const;

    uint32_t GetStackSize() const;
};
}

#endif //QM_MODEL_PROCESS_HPP
