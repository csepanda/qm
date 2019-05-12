#ifndef QM_ALGORITHM_GRAPH_HIERARCHICALCLUSTERING_HPP
#define QM_ALGORITHM_GRAPH_HIERARCHICALCLUSTERING_HPP

#include "Cluster.hpp"

namespace qm::algorithm::graph {
namespace HAC {
enum class Affinity {
    Euclidian
};

enum class Linkage {
    Average,
    Ward
};
}

template<typename TNode, typename TEdge>
const std::vector<Cluster<TNode, TEdge>> HierarchicalClustering(
  const Graph<TNode, TEdge> &graph,
  uint32_t clustersCount,
  HAC::Affinity affinity = HAC::Affinity::Euclidian,
  HAC::Linkage linkage = HAC::Linkage::Average
);
}

#include "HierarchicalClustering.tpp"

#endif //QM_ALGORITHM_GRAPH_HIERARCHICALCLUSTERING_HPP
