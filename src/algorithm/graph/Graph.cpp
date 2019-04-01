#include <qm/algorithm/graph/Graph.hpp>

namespace qm::algorithm::graph {
template<typename TNode, typename TEdge>
Graph<TNode, TEdge>::Graph(
  std::vector<std::shared_ptr<Vertex<TNode, TEdge>>> vertices,
  std::vector<std::shared_ptr<Edge<TNode, TEdge>>> edges
)
  : m_vertices{vertices},
    m_edges{edges} {

    std::map<std::shared_ptr<Vertex<TNode, TEdge>>, uint32_t> verticesIds;

    for (auto i = 0; i < vertices.size(); i++) {
        verticesIds[vertices[i]] = i;
    }

    m_verticesIds = verticesIds;
}

template<typename TNode, typename TEdge>
const std::vector<std::shared_ptr<Vertex<TNode, TEdge>>> &Graph<TNode, TEdge>::GetVertices() const {
    return m_vertices;
}

template<typename TNode, typename TEdge>
const std::vector<std::shared_ptr<Edge<TNode, TEdge>>> &Graph<TNode, TEdge>::GetEdges() const {
    return m_edges;
}

template<typename TNode, typename TEdge>
const uint32_t Graph<TNode, TEdge>::GetVertexId(const std::shared_ptr<Vertex<TNode, TEdge>> &vertex) const {
    return m_verticesIds[vertex];
}

template<typename TNode, typename TEdge>
const std::shared_ptr<Vertex<TNode, TEdge>> &Graph<TNode, TEdge>::GetVertexById(const uint32_t id) const {
    return m_vertices[id];
}
}