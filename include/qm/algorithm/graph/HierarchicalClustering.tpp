#ifndef QM_ALGORITHM_GRAPH_HIERARCHICALCLUSTERING_TPP
#define QM_ALGORITHM_GRAPH_HIERARCHICALCLUSTERING_TPP

#include <cmath>
#include <gmpxx.h>
#include "Cluster.hpp"
#include "HierarchicalClustering.hpp"

namespace qm::algorithm::graph {

static double computeDistance(
  const std::vector<double> &a,
  const std::vector<double> &b,
  HAC::Affinity affinity = HAC::Affinity::Euclidian
) {
    if (a.size() != b.size()) {
        throw std::invalid_argument("vector size should be same");
    }

    switch (affinity) {
        case HAC::Affinity::Euclidian: {
            double sum = 0;

            for (uint32_t i = 0; i < a.size(); ++i) {
                sum += std::pow(b[i] - a[i], 2);
            }

            return std::sqrt(sum);
        }
        default:
            throw std::logic_error("required affinity is not implemented");
    }
}

static double Linkage(
  const matrix::Matrix &distanceMatrix,
  const std::vector<uint32_t> cluster1,
  const std::vector<uint32_t> cluster2,
  HAC::Linkage linkageMethod
) {
    uint32_t linkage = 0;

    switch (linkageMethod) {
        case HAC::Linkage::Average: {
            for (const auto &i : cluster1) {
                for (const auto &j : cluster2) {
                    linkage += distanceMatrix.Get(i, j);
                }
            }

            linkage /= cluster1.size() * cluster2.size();

            break;
        }
        default:
            throw std::logic_error("required linkage method is not implemented");
    }

    return linkage;
}

template<typename TNode, typename TEdge>
const std::vector<Cluster < TNode, TEdge>> HierarchicalClustering(
  const Graph <TNode, TEdge> &graph,
  uint32_t clustersCount,
  HAC::Affinity affinity,
  HAC::Linkage linkage
) {
    auto adjacencyMatrix = graph.AdjacencyMatrix(true);
    auto vertexCount = adjacencyMatrix.GetColumnsCount();
    matrix::Matrix distanceMatrix(vertexCount, vertexCount);
    std::vector<std::vector<uint32_t>> clusters{vertexCount, std::vector<uint32_t>{}};

    // pre-compute distances
    for (uint32_t i = 0; i < vertexCount; ++i) {
        const auto a = adjacencyMatrix.GetRow(i);
        clusters[i].push_back(i);
        for (uint32_t j = 0; j < vertexCount; ++j) {
            if (i == j) {
                distanceMatrix.Set(i, j, 0);
                break;
            }

            const auto b = adjacencyMatrix.GetRow(j);
            const auto distance = computeDistance(a, b, affinity);

            distanceMatrix.Set(i, j, distance);
            distanceMatrix.Set(j, i, distance);
        }
    }

    // normalize distances according to the connectivity of the graph
    for (uint32_t i = 0; i < vertexCount; ++i) {
        for (uint32_t j = 0; j < vertexCount; ++j) {
            if (i == j) {
                distanceMatrix.Set(i, j, 0);
                break;
            }

            if (adjacencyMatrix.Get(i, j) == 0) {
                const auto dist = distanceMatrix.Get(i, j) * vertexCount;
                distanceMatrix.Set(i, j, dist);
                distanceMatrix.Set(j, i, dist);
            }
        }
    }

    while (clusters.size() > clustersCount) {
        double minMetric = std::numeric_limits<double>::max();
        auto minCluster1 = clusters.begin(), minCluster2 = clusters.begin();

        for (auto firstIt = clusters.begin(); firstIt < clusters.end(); ++firstIt) {
            for (auto secondIt = clusters.begin(); secondIt < clusters.end(); ++secondIt) {
                if (firstIt == secondIt) {
                    continue;
                }

                const auto compareCriteria = Linkage(distanceMatrix, *firstIt, *secondIt, linkage);
                if (compareCriteria <= minMetric) {
                    minMetric = compareCriteria;
                    minCluster1 = firstIt;
                    minCluster2 = secondIt;
                }
            }
        }

        for (const auto &vertex : *minCluster2) {
            (*minCluster1).push_back(vertex);
        }

        clusters.erase(minCluster2);
    }

    std::vector<Cluster<TNode, TEdge>> resultClusters{};

    for (auto it = clusters.begin(); it < clusters.end(); ++it) {
        const int label = static_cast<const int>(std::distance(clusters.begin(), it));
        std::vector<std::shared_ptr<Vertex<TNode, TEdge>>> vertices;

        for (const auto &index : *it) {
            vertices.push_back(graph.GetVertexById(index));
        }

        resultClusters.push_back(Cluster<TNode, TEdge>(label, std::move(vertices)));
    }

    return resultClusters;
}
}

#endif //QM_ALGORITHM_GRAPH_HIERARCHICALCLUSTERING_TPP
