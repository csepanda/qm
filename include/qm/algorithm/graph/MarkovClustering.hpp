#ifndef QM_ALGORITHM_GRAPH_MARKOVCHAINCLUSTERING_HPP
#define QM_ALGORITHM_GRAPH_MARKOVCHAINCLUSTERING_HPP

#include <memory>
#include <vector>
#include "Vertex.hpp"
#include "Graph.hpp"
#include "Cluster.hpp"

namespace qm::algorithm::graph {
template<typename TNode, typename TEdge>
const std::vector<Cluster<TNode, TEdge>> MarkovClustering(
  const Graph<TNode, TEdge> &graph,
  uint32_t powerParam,
  uint32_t inflationParam
);
}

#include "MarkovClustering.tpp"

#endif //QM_ALGORITHM_GRAPH_MARKOVCHAINCLUSTERING_HPP
