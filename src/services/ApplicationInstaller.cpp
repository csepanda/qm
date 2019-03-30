#include <qm/services/ApplicationInstaller.hpp>
#include <ns3/dce-application-helper.h>
#include <ns3/mpi-interface.h>

namespace qm::services {

ApplicationInstaller::ApplicationInstaller(std::shared_ptr<TimeSequence> timer) : m_timer{std::move(timer)} {
}

void ApplicationInstaller::Install(std::vector<std::shared_ptr<qm::models::Process>> &processes) {
    ns3::DceApplicationHelper applicationHelper;

    for (const auto &process : processes) {
        if (ns3::MpiInterface::IsEnabled() &&
            ns3::MpiInterface::GetSystemId() != process->GetNode()->GetSystemId()) { // TODO refactor
            continue;
        }

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

        if (time == 0) {
            time = m_timer->NextSeconds();
        } else if (m_timer->CurrentSeconds().ToDouble(ns3::Time::Unit::S) < time.ToDouble(ns3::Time::Unit::S)) {
            m_timer->SetSeconds(time);
        }

        appContainer.Start(time);
    }
}
}
