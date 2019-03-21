#include <qm/services/mpi/ManualSystemIdMarkerStrategy.hpp>

namespace qm::services::mpi {

uint32_t ManualSystemIdMarkerStrategy::GetSystemIdFor(uint64_t nodeIndex) {
    return m_network.GetNodes()[nodeIndex]->GetSystemId();
}

ManualSystemIdMarkerStrategy::ManualSystemIdMarkerStrategy(const models::Network &network, uint32_t systemSize)
  : ISystemIdMarkerStrategy(network, systemSize) {}

std::unique_ptr<ISystemIdMarkerStrategy>
ManualSystemIdMarkerStrategyProducer::Create(const qm::models::Network &network, uint32_t systemSize) {
    return std::unique_ptr<ISystemIdMarkerStrategy>(new ManualSystemIdMarkerStrategy{network, systemSize});
}
}
