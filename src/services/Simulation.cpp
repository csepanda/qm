#include <utility>

#include <utility>

#include <utility>

#include <algorithm>
#include <utility>

#include <ns3/node-container.h>
#include <ns3/point-to-point-helper.h>

#include <qm/exceptions.hpp>
#include <qm/models.hpp>
#include <qm/services/dce/LinuxStackIPConfigurator.hpp>
#include <qm/services/Simulation.hpp>

namespace qm::services {

Simulation::Simulation(
  ns3::Time stopTime,
  qm::models::Network network,
  std::vector<std::shared_ptr<qm::models::Process>> applications,
  std::shared_ptr<TimeSequence> timer,
  std::shared_ptr<ns3::DceManagerHelper> dceManager
)
  : m_stopTime {std::move(stopTime)},
    m_network{std::move(network)},
    m_applications{std::move(applications)},
    m_timer{std::move(timer)},
    m_dceManager{std::move(dceManager)} {

    /* constructor*/

}

void Simulation::Run() {
    if (m_stopTime == 0) {
        m_stopTime = m_timer->NextSeconds();
    }

    if (m_stopTime < m_timer->CurrentSeconds()) {
        std::stringstream ss;

        ss << "Simulation stop time cannot be less then last initialization timer time: ";
        ss << "StopTime: " << m_stopTime.GetSeconds() << "s\n";
        ss << "Timer's time: " << m_timer->CurrentSeconds() << "s\n";
        throw InitializationException(ss.str(), "Simulation::Run");
    }

    ns3::Simulator::Stop(m_stopTime);
    ns3::Simulator::Run();
    ns3::Simulator::Destroy();
}
}
