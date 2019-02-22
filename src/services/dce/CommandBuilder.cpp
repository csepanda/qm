#include <utility>

#include <ns3/application-container.h>
#include <ns3/dce-module.h>
#include <ns3/nstime.h>

#include <qm/services/dce/CommandBuilder.hpp>

namespace qm::services::dce {

void CommandBuilder::Execute(ns3::Time at) {
    validateCommand();

    ns3::DceApplicationHelper process;
    ns3::ApplicationContainer apps;
    process.SetBinary(m_binary);
    process.SetStackSize(m_stackSize);
    process.ResetArguments();
    process.ParseArguments(m_arguments);
    apps = process.Install(m_node);
    apps.Start(std::move(at));
}

CommandBuilder &CommandBuilder::SetNode(const ns3::Ptr<ns3::Node> &node) {
    m_node = node;
    return *this;
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
    m_arguments = std::move(arguments);
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
}
