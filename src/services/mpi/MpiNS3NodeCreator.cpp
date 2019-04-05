#include <qm/services/mpi/MpiNS3NodeCreator.hpp>

namespace qm::services::mpi {

MpiNS3NodeCreator::MpiNS3NodeCreator(
  uint32_t systemId,
  uint32_t systemSize,
  std::unique_ptr<ISystemIdMarkerStrategyProducer> markerStrategyProducer
)
  : m_systemId{systemId},
    m_systemSize{systemSize},
    m_markerStrategyProducer{std::move(markerStrategyProducer)} {
}

void MpiNS3NodeCreator::Create(qm::models::Network &network) {
    const auto markerStrategy = m_markerStrategyProducer->Create(network, m_systemSize);

    auto &nodes = network.GetNodes();
    for (const auto &node : nodes) {
        const auto systemId = markerStrategy->GetSystemIdFor(node->GetId());

        node->SetSystemId(systemId);
        node->SetNS3Node(ns3::CreateObject<ns3::Node>(systemId));
    }
}
}
