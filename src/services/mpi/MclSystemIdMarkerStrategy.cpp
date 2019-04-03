#include <qm/services/mpi/MclSystemIdMarkerStrategy.hpp>
#include <qm/services/converters/NetworkToGraph.hpp>
#include <qm/algorithm/graph/MarkovClustering.hpp>

namespace qm::services::mpi {

uint32_t MclSystemIdMarkerStrategy::GetSystemIdFor(const std::string &nodeId) {
    return m_systemIds.at(nodeId) % m_systemSize;
}

constexpr unsigned int POWER_PARAMETER = 2;
constexpr unsigned int INFLATION_PARAMETER = 2;
MclSystemIdMarkerStrategy::MclSystemIdMarkerStrategy(const models::Network &network, uint32_t systemSize)
  : ISystemIdMarkerStrategy(network, systemSize) {
    const auto graph = qm::services::converters::ConvertNetworkToGraph(network);
    const auto clusters = qm::algorithm::graph::MarkovClustering(graph, POWER_PARAMETER, INFLATION_PARAMETER);

    std::map<const std::string, uint32_t> systemIds{};

    for (uint32_t i = 0; i < clusters.size(); ++i) {
        const auto &vertices = clusters[i].GetVertices();

        for (const auto &vertex : vertices) {

            systemIds[vertex->GetBackingNode()->GetId()] = i;
        }
    }

    m_systemIds = systemIds;
}

std::unique_ptr<ISystemIdMarkerStrategy>
MclSystemIdMarkerStrategyProducer::Create(const qm::models::Network &network, uint32_t systemSize) {
    return std::unique_ptr<ISystemIdMarkerStrategy>(new MclSystemIdMarkerStrategy{network, systemSize});
}
}


