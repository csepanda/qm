#include <memory>

#include <utility>

#include <ns3/application-container.h>
#include <ns3/dce-module.h>
#include <ns3/nstime.h>

#include <qm/services/dce/CommandBuilder.hpp>
#include <qm/models/Process.hpp>

namespace qm::services::dce {

void CommandBuilder::Execute() {
    Execute(ns3::Time(0));
}

void CommandBuilder::Execute(ns3::Time at) {
    validateCommand();

    m_appInstaller->Install(std::make_shared<qm::models::Process>(
      m_node, m_binary, m_stackSize, m_arguments, std::move(at)
    ));
}

CommandBuilder &CommandBuilder::SetBinary(std::string binary) {
    m_binary = std::move(binary);
    return *this;
}

CommandBuilder &CommandBuilder::SetStackSize(uint32_t stackSize) {
    m_stackSize = stackSize;
    return *this;
}

CommandBuilder &CommandBuilder::SetArguments(std::string arguments) {
    m_arguments.clear();
    m_arguments.push_back(std::move(arguments));
    return *this;
}

void CommandBuilder::validateCommand() const {
    if (m_binary.empty()) {
        throw std::logic_error("Binary to run is not specified");
    }

    if (m_node == nullptr) {
        throw std::logic_error("Node on which command will be executed is not specified");
    }
}

CommandBuilder &CommandBuilder::SetNode(const std::shared_ptr<qm::models::Node> &node) {
    m_node = node;
    return *this;
}
}
