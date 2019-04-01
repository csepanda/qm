#include <qm/algorithm/graph/Graph.hpp>

namespace qm::algorithm::graph {
template<typename TNode, typename TEdge>
Graph<TNode, TEdge>::Graph(
  std::vector<std::shared_ptr<Vertex<TNode, TEdge>>> vertices,
  std::vector<std::shared_ptr<Edge<TNode, TEdge>>> edges
)
  : m_vertices{vertices},
    m_edges{edges} {

}

template<typename TNode, typename TEdge>
const std::vector<std::shared_ptr<Vertex<TNode, TEdge>>> &Graph<TNode, TEdge>::GetVertices() const {
    return m_vertices;
}

template<typename TNode, typename TEdge>
const std::vector<std::shared_ptr<Edge<TNode, TEdge>>> &Graph<TNode, TEdge>::GetEdges() const {
    return m_edges;
}
}