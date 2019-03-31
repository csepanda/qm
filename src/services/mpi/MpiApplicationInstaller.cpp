#include <utility>

#include <qm/services/mpi/MpiApplicationInstaller.hpp>
#include <ns3/mpi-interface.h>

namespace qm::services::mpi {

void MpiApplicationInstaller::Install(const std::vector<std::shared_ptr<qm::models::Process>> &processes) {
    for (const auto& process : processes) {
        Install(process);
    }
}

void MpiApplicationInstaller::Install(const std::shared_ptr<qm::models::Process> &process) {
    if (ns3::MpiInterface::IsEnabled() &&
        ns3::MpiInterface::GetSystemId() != process->GetNode()->GetSystemId()) {
        return;
    }

    ApplicationInstaller::Install(process);
}

MpiApplicationInstaller::MpiApplicationInstaller(std::shared_ptr<qm::services::TimeSequence> timer)
  : ApplicationInstaller(std::move(timer)) {

}
}
