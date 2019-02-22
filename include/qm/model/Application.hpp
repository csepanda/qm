#include <utility>

#include <utility>

#include <utility>

#ifndef QM_MODEL_PROCESS_HPP
#define QM_MODEL_PROCESS_HPP

#include <string>
#include <vector>
#include "node.hpp"

namespace qm::models {
class Application {
    std::shared_ptr<Node> m_node;
    std::string m_binary;
    std::vector<std::string> m_arguments;
    uint32_t m_stackSize;
public:
    Application(std::shared_ptr<Node> m_node, std::string m_binary, uint32_t m_stackSize,
                std::vector<std::string> m_arguments)
      : m_node(std::move(m_node)),
        m_binary(std::move(m_binary)),
        m_arguments(std::move(m_arguments)),
        m_stackSize(m_stackSize) {

    }

    const std::shared_ptr<Node> &GetNode() const;

    const std::string &GetBinary() const;

    const std::vector<std::string> &GetArguments() const;

    uint32_t GetStackSize() const;
};
}

#endif //QM_MODEL_PROCESS_HPP
