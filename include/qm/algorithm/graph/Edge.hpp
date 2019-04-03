#ifndef QM_ALGORITHM_GRAPH_EDGE_HPP
#define QM_ALGORITHM_GRAPH_EDGE_HPP

#include <memory>
#include <vector>

#include "Vertex.hpp"

namespace qm::algorithm::graph {
template<typename TNode, typename TEdge>
class Vertex;

template<typename TNode, typename TEdge>
class Edge {
    int m_weight;
    std::shared_ptr<TEdge> m_backingEdge;
    std::weak_ptr<Vertex<TNode, TEdge>> m_start;
    std::weak_ptr<Vertex<TNode, TEdge>> m_end;
public:
    Edge(
      int weight,
      const std::shared_ptr<TEdge> &backingEdge,
      const std::weak_ptr<Vertex<TNode, TEdge>> &startVertex,
      const std::weak_ptr<Vertex<TNode, TEdge>> &endVertex
    );

    const int GetWeight() const;

    const std::shared_ptr<TEdge> &GetBackingEdge() const;

    const std::weak_ptr<Vertex<TNode, TEdge>> &GetStartVertex() const;

    const std::weak_ptr<Vertex<TNode, TEdge>> &GetEndVertex() const;
};
}

#include "Edge.tpp"

#endif //QM_ALGORITHM_GRAPH_EDGE_HPP
