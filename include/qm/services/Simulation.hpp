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
    std::vector<std::shared_ptr<qm::models::Process>> m_applications;
    std::shared_ptr<TimeSequence> m_timer;
    std::shared_ptr<ns3::DceManagerHelper> m_dceManager;
public:
    Simulation(
      qm::models::Network,
      std::vector<std::shared_ptr<qm::models::Process>>,
      std::shared_ptr<TimeSequence>,
      std::shared_ptr<ns3::DceManagerHelper>
    );

    void Run();
};
}

#endif //QM_SIMULATION_H
