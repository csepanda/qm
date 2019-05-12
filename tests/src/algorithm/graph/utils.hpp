#ifndef TEST_QM_ALGORITHM_GRAPH_UTILS_HPP
#define TEST_QM_ALGORITHM_GRAPH_UTILS_HPP

#include <qm/algorithm/graph/Vertex.hpp>
#include <qm/algorithm/graph/Edge.hpp>
#include <qm/algorithm/graph/Graph.hpp>

using namespace std;
using namespace qm::algorithm::graph;

namespace tests::qm::algorithm::graph::utils {
Graph<int, int> buildGraph(const vector<vector<int>> &adjacencyMatrix);
}

#endif //TEST_QM_ALGORITHM_GRAPH_UTILS_HPP
