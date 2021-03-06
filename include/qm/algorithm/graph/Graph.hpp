#ifndef QM_ALGORITHM_GRAPH_GRAPH_HPP
#define QM_ALGORITHM_GRAPH_GRAPH_HPP

#include <map>
#include <memory>
#include <vector>
#include <qm/algorithm/graph/Vertex.hpp>
#include <qm/algorithm/graph/Edge.hpp>
#include <qm/algorithm/matrix/Matrix.hpp>

namespace qm::algorithm::graph {
template<typename TNode, typename TEdge>
class Edge;

template<typename TNode, typename TEdge>
class Vertex;

template<typename TNode, typename TEdge>
class Graph {
    const std::vector<std::shared_ptr<Vertex<TNode, TEdge>>> m_vertices;
    const std::vector<std::shared_ptr<Edge<TNode, TEdge>>> m_edges;
    std::map<std::shared_ptr<Vertex<TNode, TEdge>>, uint32_t> m_verticesIds;
public:
    Graph(
      std::vector<std::shared_ptr<Vertex<TNode, TEdge>>> vertices,
      std::vector<std::shared_ptr<Edge<TNode, TEdge>>> edges
    );

    const std::vector<std::shared_ptr<Vertex<TNode, TEdge>>> &GetVertices() const;

    const std::vector<std::shared_ptr<Edge<TNode, TEdge>>> &GetEdges() const;

    const uint32_t GetVertexId(const std::shared_ptr<Vertex<TNode, TEdge>> &) const;

    const std::shared_ptr<Vertex<TNode, TEdge>> &GetVertexById(const uint32_t id) const;

    matrix::Matrix AdjacencyMatrix(bool selfLoops = false) const;
};
}

#include "Graph.tpp"

#endif //QM_ALGORITHM_GRAPH_GRAPH_HPP
