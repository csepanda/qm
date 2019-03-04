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
  qm::models::Network network,
  std::vector<std::shared_ptr<qm::models::Process>> applications,
  std::shared_ptr<TimeSequence> timer,
  std::shared_ptr<ns3::DceManagerHelper> dceManager
)
  : m_network{std::move(network)},
    m_applications{std::move(applications)},
    m_timer{std::move(timer)},
    m_dceManager{std::move(dceManager)} {

    /* constructor*/

}

// TODO implement
void Simulation::Run() {
    throw std::logic_error("TODO implement");
}
}
