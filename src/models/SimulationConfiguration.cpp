#include <utility>

#include <qm/models.hpp>
#include <qm/models/SimulationConfiguration.hpp>


namespace qm::models {
NetworkStack SimulationConfiguration::GetNetworkStack() const {
    return m_networkStack;
}

SimulationConfiguration::SimulationConfiguration(
  NetworkStack networkStack,
  ns3::Time stopTime,
  bool enableMpi
)
  : m_networkStack{networkStack},
    m_stopTime{std::move(stopTime)},
    m_mpi{enableMpi} {
}

ns3::Time SimulationConfiguration::GetStopTime() const {
    return m_stopTime;
}
}

