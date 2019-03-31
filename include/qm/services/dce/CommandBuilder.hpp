#include <utility>

#ifndef QM_SERVICES_DCE_COMMANDBUILDER_H
#define QM_SERVICES_DCE_COMMANDBUILDER_H

#include <ns3/string.h>
#include <ns3/node.h>
#include <qm/models/Node.hpp>
#include <qm/services/TimeSequence.h>
#include <memory>
#include <qm/services/ApplicationInstaller.hpp>

namespace qm::services::dce {
class CommandBuilder {
    std::shared_ptr<qm::services::ApplicationInstaller> m_appInstaller;

    std::shared_ptr<qm::models::Node> m_node;
    std::string m_binary;
    std::vector<std::string> m_arguments;
    uint32_t m_stackSize = 1 << 16;

    void validateCommand() const;

public:
    CommandBuilder(std::shared_ptr<qm::services::ApplicationInstaller> appInstaller)
      : m_appInstaller{std::move(appInstaller)} {}

    CommandBuilder &SetNode(const std::shared_ptr<qm::models::Node> &node);

    CommandBuilder &SetBinary(std::string binary);

    CommandBuilder &SetStackSize(uint32_t stackSize);

    CommandBuilder &SetArguments(std::string arguments);

    void Execute();
    void Execute(ns3::Time at);
};
}

#endif //QM_COMMANDBUILDER_H
