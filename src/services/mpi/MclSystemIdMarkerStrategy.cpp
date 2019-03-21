#include <qm/services/mpi/MclSystemIdMarkerStrategy.hpp>

namespace qm::services::mpi {

uint32_t MclSystemIdMarkerStrategy::GetSystemIdFor(uint64_t nodeIndex) {
    throw std::logic_error("MclSystemIdMarkerStrategy::GetSystemIdFor is not implemented");
}

MclSystemIdMarkerStrategy::MclSystemIdMarkerStrategy(const models::Network &network, uint32_t systemSize)
  : ISystemIdMarkerStrategy(network, systemSize) {}

std::unique_ptr<ISystemIdMarkerStrategy>
MclSystemIdMarkerStrategyProducer::Create(const qm::models::Network &network, uint32_t systemSize) {
    return std::unique_ptr<ISystemIdMarkerStrategy>(new MclSystemIdMarkerStrategy{network, systemSize});
}
}


