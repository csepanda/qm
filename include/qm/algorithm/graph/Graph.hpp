#ifndef QM_ALGORITHM_GRAPH_GRAPH_HPP
#define QM_ALGORITHM_GRAPH_GRAPH_HPP

#include <memory>
#include "Vertex.hpp"

namespace qm::algorithm::graph {
template<typename TNode, typename TEdge>
class Graph {
    std::vector<std::shared_ptr<Vertex<TNode, TEdge>>> m_vertices;
    std::vector<std::shared_ptr<Edge<TNode, TEdge>>> m_edges;
public:
    Graph(
      std::vector<std::shared_ptr<Vertex<TNode, TEdge>>> vertices,
      std::vector<std::shared_ptr<Edge<TNode, TEdge>>> edges
    );

    const std::vector<std::shared_ptr<Vertex<TNode, TEdge>>> &GetVertices() const;

    const std::vector<std::shared_ptr<Edge<TNode, TEdge>>> &GetEdges() const;
};
}

#endif //QM_ALGORITHM_GRAPH_GRAPH_HPP
