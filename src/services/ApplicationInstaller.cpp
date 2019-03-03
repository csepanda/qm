#include <qm/services/ApplicationInstaller.hpp>
#include <ns3/dce-application-helper.h>

namespace qm::services {

ApplicationInstaller::ApplicationInstaller(std::shared_ptr<TimeSequence> timer) : m_timer{std::move(timer)}{
}

void ApplicationInstaller::Install(std::vector<std::shared_ptr<qm::models::Process>> &processes) {
    ns3::DceApplicationHelper applicationHelper;

    for (const auto& process : processes) {
        applicationHelper.SetBinary(process->GetBinary());
        applicationHelper.SetStackSize(process->GetStackSize());
        applicationHelper.ResetArguments();
        applicationHelper.ResetEnvironment();

        for (const auto& argument : process->GetArguments()) {
            applicationHelper.AddArgument(argument);
        }

        auto appContainer = applicationHelper.Install(process->GetNode()->GetNS3Node());

        if (process->GetStartTime() == 0) {
            appContainer.Start(m_timer->NextSeconds());
        } else {
            appContainer.Start(process->GetStartTime());
        }
    }
}
}
