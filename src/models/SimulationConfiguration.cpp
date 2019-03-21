#include <utility>

#include <qm/models.hpp>
#include <qm/models/SimulationConfiguration.hpp>


namespace qm::models {
SimulationConfiguration::SimulationConfiguration(
  NetworkStack networkStack,
  ns3::Time stopTime,
  bool enableMpi,
  SystemIdMarkerStrategy m_systemIdMarkerStrategy
)
  : m_networkStack{networkStack},
    m_stopTime{std::move(stopTime)},
    m_mpi{enableMpi},
    m_systemIdMarkerStrategy(m_systemIdMarkerStrategy) {
}

NetworkStack SimulationConfiguration::GetNetworkStack() const {
    return m_networkStack;
}

ns3::Time SimulationConfiguration::GetStopTime() const {
    return m_stopTime;
}

SystemIdMarkerStrategy SimulationConfiguration::GetSystemIdMarkerStrategy() const {
    return m_systemIdMarkerStrategy;
}

bool SimulationConfiguration::IsMpiEnabled() const {
    return m_mpi;
}
}

