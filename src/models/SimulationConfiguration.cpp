
#include <qm/model/SimulationConfiguration.hpp>

namespace qm::models {
NetworkStack SimulationConfiguration::GetNetworkStack() const {
    return m_networkStack;
}

SimulationConfiguration::SimulationConfiguration(NetworkStack networkStack) {
    m_networkStack = networkStack;
}
}

