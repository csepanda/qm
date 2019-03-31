#ifndef QM_SIMULATIONPRODUCER_H
#define QM_SIMULATIONPRODUCER_H

#include <qm/models.hpp>
#include "Simulation.hpp"
#include "TimeSequence.h"
#include "NetworkConfigurator.hpp"
#include "ApplicationInstaller.hpp"

namespace qm::services {
class SimulationProducer {
    qm::models::SimulationConfiguration m_cfg;
public:
    explicit SimulationProducer(qm::models::SimulationConfiguration cfg);
    qm::services::Simulation Create(
      qm::models::Network,
      std::vector<std::shared_ptr<qm::models::Process>>
    );

private:
    std::unique_ptr<INs3NodeCreator> produceNodeCreator();
    std::shared_ptr<ApplicationInstaller> produceApplicationInstaller(std::shared_ptr<TimeSequence> &timer);
};
}

#endif //QM_SIMULATIONPRODUCER_H
