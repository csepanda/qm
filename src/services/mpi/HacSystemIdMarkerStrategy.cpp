#include <qm/services/mpi/HacSystemIdMarkerStrategy.hpp>
#include <qm/services/converters/NetworkToGraph.hpp>
#include <qm/algorithm/graph/HierarchicalClustering.hpp>

namespace qm::services::mpi {

uint32_t HacSystemIdMarkerStrategy::GetSystemIdFor(const std::string &nodeId) {
    const auto sid = m_systemIds.at(nodeId);

    return sid;
}

constexpr unsigned int POWER_PARAMETER = 2;
constexpr unsigned int INFLATION_PARAMETER = 2;
HacSystemIdMarkerStrategy::HacSystemIdMarkerStrategy(const models::Network &network, uint32_t systemSize)
  : ISystemIdMarkerStrategy(network, systemSize) {

    const auto graph = qm::services::converters::ConvertNetworkToGraph(network);
    const auto clusters = qm::algorithm::graph::HierarchicalClustering(graph, systemSize);

    std::map<const std::string, uint32_t> systemIds{};

    for (auto it = clusters.begin(); it != clusters.end(); ++it) {
        const auto label = static_cast<uint32_t >(std::distance(clusters.begin(), it));
        const auto &vertices = it->GetVertices();

        for (const auto &vertex : vertices) {
            systemIds[vertex->GetBackingNode()->GetId()] = label;
        }
    }

    m_systemIds = systemIds;
}

std::unique_ptr<ISystemIdMarkerStrategy>
HacSystemIdMarkerStrategyProducer::Create(const qm::models::Network &network, uint32_t systemSize) {
    return std::unique_ptr<ISystemIdMarkerStrategy>(new HacSystemIdMarkerStrategy{network, systemSize});
}
}


