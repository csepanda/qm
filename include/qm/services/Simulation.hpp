//
// Created by cspanda on 2/22/19.
//

#ifndef QM_SERVICES_SIMULATION_H
#define QM_SERVICES_SIMULATION_H

#include <qm/model.hpp>
#include "IpConfigurator.hpp"

namespace qm::services {
class Simulation {
    qm::models::Network m_network;
    std::shared_ptr<ns3::DceManagerHelper> m_dceManager;
    std::unique_ptr<qm::services::IpConfigurator> m_ipConfigurator;

    void ConfigureP2PConnection(const std::shared_ptr<qm::models::PointToPointConnection> &connection);
public:
    Simulation(qm::models::SimulationConfiguration, qm::models::Network, std::shared_ptr<TimeSequence> timeSequence);

    void ConfigureNetwork();
};
}

#endif //QM_SIMULATION_H
