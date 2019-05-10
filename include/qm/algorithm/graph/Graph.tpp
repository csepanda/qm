#include <map>
#include <memory>
#include <vector>
#include <qm/algorithm/graph/Vertex.hpp>
#include <qm/algorithm/graph/Edge.hpp>

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
    return m_verticesIds.at(vertex);
}

template<typename TNode, typename TEdge>
const std::shared_ptr<Vertex<TNode, TEdge>> &Graph<TNode, TEdge>::GetVertexById(const uint32_t id) const {
    return m_vertices[id];
}

template<typename TNode, typename TEdge>
matrix::Matrix Graph<TNode, TEdge>::AdjacencyMatrix(bool selfLoops) const {
    const auto verticesCount = static_cast<const uint32_t>(m_vertices.size());

    matrix::Matrix matrix(verticesCount, verticesCount);

    for (const std::shared_ptr<Edge<TNode, TEdge>> &edge : m_edges) {
        const auto start = edge->GetStartVertex().lock();
        const auto end = edge->GetEndVertex().lock();

        const auto startIndex = GetVertexId(start);
        const auto endIndex = GetVertexId(end);

        matrix.Set(startIndex, endIndex, 1);
        matrix.Set(endIndex, startIndex, 1);
    }

    if (selfLoops) {
        for (uint32_t i = 0; i < verticesCount; i++) {
            matrix.Set(i, i, 1);
        }
    }

    return matrix;
}
}
