#include <utility>

#include <ns3/dce-module.h>
#include <qm/services/SimulationProducer.hpp>
#include <qm/services/NetworkConfigurator.hpp>
#include <qm/services/ApplicationInstaller.hpp>

namespace qm::services {
Simulation SimulationProducer::Create(
  qm::models::Network network,
  std::vector<std::shared_ptr<qm::models::Process>> applications
) {
    auto timer = std::make_shared<TimeSequence>();
    auto dceManagerHelper = std::make_shared<ns3::DceManagerHelper>();
    auto networkStack = m_cfg.GetNetworkStack();

    NetworkConfigurator{networkStack, timer, dceManagerHelper}
        .Configure(network);

    ApplicationInstaller{timer}
        .Install(applications);

    Simulation simulation{
        std::move(m_cfg.GetStopTime()),
        std::move(network),
        std::move(applications),
        std::move(timer),
        std::move(dceManagerHelper)
    };

    return simulation;
}

SimulationProducer::SimulationProducer(qm::models::SimulationConfiguration cfg) : m_cfg{std::move(cfg)} {
}
}

