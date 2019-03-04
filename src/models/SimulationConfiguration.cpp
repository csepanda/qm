#include <qm/models.hpp>
#include <qm/models/SimulationConfiguration.hpp>


namespace qm::models {
NetworkStack SimulationConfiguration::GetNetworkStack() const {
    return m_networkStack;
}

SimulationConfiguration::SimulationConfiguration(
  NetworkStack networkStack,
  ns3::Time stopTime
)
  : m_networkStack{networkStack},
    m_stopTime{m_stopTime} {
}

ns3::Time SimulationConfiguration::GetStopTime() const {
    return m_stopTime;
}
}

