#include <memory>

#include <utility>

#include <ns3/dce-module.h>
#include <ns3/mpi-interface.h>
#include <qm/services/SimulationProducer.hpp>
#include <qm/services/NetworkConfigurator.hpp>
#include <qm/services/ApplicationInstaller.hpp>
#include <qm/services/FilesInstaller.hpp>
#include <qm/services/SimpleNs3NodeCreator.hpp>
#include <qm/services/mpi/MpiNS3NodeCreator.hpp>
#include <qm/exceptions.hpp>
#include <qm/services/mpi/ManualSystemIdMarkerStrategy.hpp>
#include <qm/services/mpi/MclSystemIdMarkerStrategy.hpp>

namespace qm::services {
Simulation SimulationProducer::Create(
  qm::models::Network network,
  std::vector<std::shared_ptr<qm::models::Process>> applications
) {
    auto timer = std::make_shared<TimeSequence>();
    auto dceManagerHelper = std::make_shared<ns3::DceManagerHelper>();
    auto networkStack = m_cfg.GetNetworkStack();

    timer->NextSeconds();

    NetworkConfigurator{
      networkStack,
      produceNodeCreator(),
      timer,
      dceManagerHelper
    }.Configure(network);

    ApplicationInstaller{timer}
      .Install(applications);

    FilesInstaller{}
      .Install(network.GetNodes());

    for (const auto &node : network.GetNodes()) {
        dceManagerHelper->Install(node->GetNS3Node());
    }

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

std::unique_ptr<qm::services::INs3NodeCreator> SimulationProducer::produceNodeCreator() {
    if (!m_cfg.IsMpiEnabled()) {
        return std::make_unique<SimpleNs3NodeCreator>();
    }

    if (!ns3::MpiInterface::IsEnabled()) {
        throw qm::InitializationException("MPI Interface should be enabled, but it wasn't", "SimulationProducer");
    }

    const auto systemId = ns3::MpiInterface::GetSystemId();
    const auto systemCount = ns3::MpiInterface::GetSize();

    std::unique_ptr<mpi::ISystemIdMarkerStrategyProducer> markerStrategyProducer;

    switch (m_cfg.GetSystemIdMarkerStrategy()) {
        case models::SystemIdMarkerStrategy::Manual:
            markerStrategyProducer = std::make_unique<mpi::ManualSystemIdMarkerStrategyProducer>();
            break;
        case models::SystemIdMarkerStrategy::Mlc:
            markerStrategyProducer = std::make_unique<mpi::MclSystemIdMarkerStrategyProducer>();
            break;
        default:
            throw std::logic_error(
              "SimulationProducer::produceNodeCreator: Unhandled value of SystemIdMarkerStrategy enum: " +
              std::to_string((int) m_cfg.GetSystemIdMarkerStrategy()));
    }

    return std::make_unique<mpi::MpiNS3NodeCreator>(systemId, systemCount, std::move(markerStrategyProducer));
}
}

