#include <algorithm>
#include <qm/services/mpi/ManualSystemIdMarkerStrategy.hpp>

namespace qm::services::mpi {

uint32_t ManualSystemIdMarkerStrategy::GetSystemIdFor(const std::string &nodeId) {
    const auto &node = std::find_if(m_network.GetNodes().begin(), m_network.GetNodes().end(), [nodeId](const auto &node) -> bool{
        return nodeId == node->GetId();
    });

    if (node == m_network.GetNodes().end()) {
        throw std::logic_error("Cannot find node with id '" + nodeId + "'");
    }

    return (*node)->GetSystemId();
}

ManualSystemIdMarkerStrategy::ManualSystemIdMarkerStrategy(const models::Network &network, uint32_t systemSize)
  : ISystemIdMarkerStrategy(network, systemSize) {}

std::unique_ptr<ISystemIdMarkerStrategy>
ManualSystemIdMarkerStrategyProducer::Create(const qm::models::Network &network, uint32_t systemSize) {
    return std::unique_ptr<ISystemIdMarkerStrategy>(new ManualSystemIdMarkerStrategy{network, systemSize});
}
}
