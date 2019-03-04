#ifndef QM_SIMULATIONPRODUCER_H
#define QM_SIMULATIONPRODUCER_H

#include <qm/models.hpp>
#include "Simulation.hpp"
#include "TimeSequence.h"
#include "NetworkConfigurator.hpp"

namespace qm::services {
class SimulationProducer {
    qm::models::SimulationConfiguration m_cfg;
public:
    SimulationProducer(qm::models::SimulationConfiguration cfg);
    qm::services::Simulation Create(
      qm::models::Network,
      std::vector<std::shared_ptr<qm::models::Process>>
    );
};
}

#endif //QM_SIMULATIONPRODUCER_H
