#include <memory>
#include <vector>

#include "Vertex.hpp"

namespace qm::algorithm::graph {
template<typename TNode, typename TEdge>
Edge<TNode, TEdge>::Edge(
  int weight,
  std::shared_ptr<TEdge> &backingEdge,
  std::weak_ptr<Vertex<TNode, TEdge>> &startVertex,
  std::weak_ptr<Vertex<TNode, TEdge>> &endVertex
)
  : m_weight{weight},
    m_backingEdge{backingEdge},
    m_start{startVertex},
    m_end{endVertex} {
}

template<typename TNode, typename TEdge>
const int Edge<TNode, TEdge>::GetWeight() const {
    return m_weight;
}

template<typename TNode, typename TEdge>
const std::shared_ptr<TEdge> &Edge<TNode, TEdge>::GetBackingEdge() const {
    return m_backingEdge;
}

template<typename TNode, typename TEdge>
const std::weak_ptr<Vertex<TNode, TEdge>> &Edge<TNode, TEdge>::GetStartVertex() const {
    return m_start;
}

template<typename TNode, typename TEdge>
const std::weak_ptr<Vertex<TNode, TEdge>> &Edge<TNode, TEdge>::GetEndVertex() const {
    return m_end;
};

}
