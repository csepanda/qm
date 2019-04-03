#include <qm/algorithm/graph/Cluster.hpp>

namespace qm::algorithm::graph {

template<typename TNode, typename TEdge>
Cluster<TNode, TEdge>::Cluster(
  int id,
  std::vector<std::shared_ptr<Vertex<TNode, TEdge>>> vertices
)
  : m_id{id},
    m_vertices{vertices} {
}

template<typename TNode, typename TEdge>
const std::vector<std::shared_ptr<Vertex<TNode, TEdge>>> &Cluster<TNode, TEdge>::GetVertices() const {
    return m_vertices;
}

}
