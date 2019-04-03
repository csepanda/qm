#ifndef QM_ALGORITHM_GRAPH_VERTEX_HPP
#define QM_ALGORITHM_GRAPH_VERTEX_HPP

#include <memory>
#include <vector>

#include "Edge.hpp"


namespace qm::algorithm::graph {
template<typename TNode, typename TEdge>
class Edge;

template<typename TNode, typename TEdge>
class Vertex {
    int m_weight;
    std::shared_ptr<TNode> m_backingNode;
    std::vector<std::shared_ptr<Edge<TNode, TEdge>>> m_edges{};
public:
    Vertex(int, std::shared_ptr<TNode> &);

    Vertex(int, std::shared_ptr<TNode> &, std::vector<std::shared_ptr<Edge<TNode, TEdge>>> &);

    const int GetWeight() const;

    const std::shared_ptr<TNode> &GetBackingNode() const;

    const std::vector<std::shared_ptr<Edge<TNode, TEdge>>> &GetEdges() const;

    void AddEdge(const std::shared_ptr<Edge<TNode, TEdge>> &);
};

}

#include "Vertex.tpp"

#endif //QM_ALGORITHM_GRAPH_VERTEX_HPP
