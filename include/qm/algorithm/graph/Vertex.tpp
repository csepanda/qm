#include <memory>
#include <vector>

#include "Edge.hpp"


namespace qm::algorithm::graph {
template<typename TNode, typename TEdge>
Vertex<TNode, TEdge>::Vertex(int weight, const std::shared_ptr<TNode> &backingNode)
  : m_weight{weight},
    m_backingNode{backingNode} {
}

template<typename TNode, typename TEdge>
Vertex<TNode, TEdge>::Vertex(
  int weight,
  const std::shared_ptr<TNode> &backingNode,
  const std::vector<std::shared_ptr<Edge<TNode, TEdge>>> &edges
)
  : m_weight{weight},
    m_backingNode{backingNode},
    m_edges{edges} {
}

template<typename TNode, typename TEdge>
const int Vertex<TNode, TEdge>::GetWeight() const {
    return m_weight;
}

template<typename TNode, typename TEdge>
const std::shared_ptr<TNode> &Vertex<TNode, TEdge>::GetBackingNode() const {
    return m_backingNode;
}

template<typename TNode, typename TEdge>
const std::vector<std::shared_ptr<Edge<TNode, TEdge>>> &Vertex<TNode, TEdge>::GetEdges() const {
    return m_edges;
}

template<typename TNode, typename TEdge>
void Vertex<TNode, TEdge>::AddEdge(const std::shared_ptr<Edge<TNode, TEdge>> &edge) {
    m_edges.push_back(edge);
}

}
