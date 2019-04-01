#ifndef QM_ALGORITHM_GRAPH_CLUSTER_HPP
#define QM_ALGORITHM_GRAPH_CLUSTER_HPP

#include <memory>
#include <vector>
#include "Vertex.hpp"
#include "Graph.hpp"

namespace qm::algorithm::graph {
template<typename TNode, typename TEdge>
class Cluster {
    int m_id;
    std::vector<std::shared_ptr<Vertex<TNode, TEdge>>> m_vertices;
public:
    Cluster(
      int id,
      std::vector<std::shared_ptr<Vertex<TNode, TEdge>>> vertices
    );

    const std::vector<std::shared_ptr<Vertex<TNode, TEdge>>> &GetVertices() const;
};
}

#endif //QM_ALGORITHM_GRAPH_CLUSTER_HPP
