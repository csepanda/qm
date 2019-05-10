#include <qm/services/ApplicationInstaller.hpp>
#include <ns3/dce-application-helper.h>

namespace qm::services {

ApplicationInstaller::ApplicationInstaller(std::shared_ptr<TimeSequence> timer) : m_timer{std::move(timer)} {
}

void ApplicationInstaller::Install(const std::shared_ptr<models::Process> &process) {
    ns3::DceApplicationHelper applicationHelper{};

    applicationHelper.SetBinary(process->GetBinary());
    applicationHelper.SetStackSize(process->GetStackSize());
    applicationHelper.ResetArguments();
    applicationHelper.ResetEnvironment();

    const auto &arguments = process->GetArguments();

    if (arguments.size() == 1) {
        applicationHelper.ParseArguments(arguments[0]);
    } else if (!arguments.empty()){
        for (const auto &argument : process->GetArguments()) {
            applicationHelper.AddArgument(argument);
        }
    }

    auto appContainer = applicationHelper.Install(process->GetNode()->GetNS3Node());
    auto time = process->GetStartTime();
    auto nodeId = process->GetNode()->GetId();

    if (time == 0) {
        time = m_timer->NextSeconds(nodeId);
    } else if (m_timer->CurrentSeconds().ToDouble(ns3::Time::Unit::S) < time.ToDouble(ns3::Time::Unit::S)) {
        m_timer->SetSeconds(time, nodeId);
    }

    appContainer.Start(time);
}

void ApplicationInstaller::Install(const std::vector<std::shared_ptr<qm::models::Process>> &processes) {
    m_timer->SetStep(0.01);

    for (const auto &process : processes) {
        Install(process);
    }
    m_timer->ResetStep();
}

}
