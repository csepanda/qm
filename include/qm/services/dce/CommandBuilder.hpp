#ifndef QM_SERVICES_DCE_COMMANDBUILDER_H
#define QM_SERVICES_DCE_COMMANDBUILDER_H

#include <ns3/string.h>
#include <ns3/node.h>

namespace qm::services::dce {
class CommandBuilder {
    ns3::Ptr<ns3::Node> m_node;
    std::string m_binary;
    std::string m_arguments;
    uint32_t m_stackSize = 1 << 16;

    void validateCommand() const;
public:
    CommandBuilder(const ns3::Ptr<ns3::Node> &node) : m_node{node} {}

    CommandBuilder& SetNode(const ns3::Ptr<ns3::Node>& node);

    CommandBuilder& SetBinary(std::string binary);

    CommandBuilder& SetStackSize(uint32_t stackSize);

    CommandBuilder& SetArguments(std::string arguments);

    void Execute(ns3::Time at);
};
}

#endif //QM_COMMANDBUILDER_H
