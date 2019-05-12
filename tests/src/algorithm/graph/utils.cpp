#include "utils.hpp"

namespace tests::qm::algorithm::graph::utils {
typedef Vertex<int, int> vertex_t;
typedef Edge<int, int> edge_t;
typedef Graph<int, int> graph_t;

graph_t buildGraph(const vector<vector<int>> &adjacencyMatrix) {
    auto size = adjacencyMatrix.size();
    vector<shared_ptr<vertex_t>> vertices;
    vector<shared_ptr<edge_t>> edges;

    for (int i = 0; i < size; i++) {
        auto value = make_shared<int>(i);
        auto vertex = make_shared<vertex_t>(0, value);

        // look only through on left diagonal half
        // self loops are ignored.
        for (int j = 0; j < i; j++) {
            if (adjacencyMatrix[i][j] == 1) {
                auto &startRef = vertex;
                auto &endRef = vertices[j];
                weak_ptr<vertex_t> start = startRef;
                weak_ptr<vertex_t> end = endRef;
                auto edgeValue = make_shared<int>(i * size * 10 + j);
                const auto edge = make_shared<edge_t>(0, edgeValue, start, end);

                startRef->AddEdge(edge);
                endRef->AddEdge(edge);

                edges.push_back(edge);
            }
        }

        vertices.push_back(vertex);
    }

    return graph_t(vertices, edges);
}
}
