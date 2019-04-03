#ifndef QM_ALGORITHM_GRAPH_MARKOVCHAINCLUSTERING_TPP
#define QM_ALGORITHM_GRAPH_MARKOVCHAINCLUSTERING_TPP
#include <qm/algorithm/matrix/Matrix.hpp>
#include <qm/algorithm/matrix/Normalization.hpp>
#include <qm/algorithm/graph/MarkovClustering.hpp>

namespace qm::algorithm::graph {

template<typename TNode, typename TEdge>
static matrix::Matrix createAssociatedMatrix(const Graph<TNode, TEdge> &graph) {
    const auto verticesCount = static_cast<const uint32_t>(graph.GetVertices().size());

    matrix::Matrix matrix(verticesCount, verticesCount);

    for (const std::shared_ptr<Edge<TNode, TEdge>> &edge : graph.GetEdges()) {
        const auto start = edge->GetStartVertex().lock();
        const auto end = edge->GetEndVertex().lock();

        const auto startIndex = graph.GetVertexId(start);
        const auto endIndex = graph.GetVertexId(end);

        matrix.Set(startIndex, endIndex, 1);
        matrix.Set(endIndex, startIndex, 1);

    }

    return matrix;
}

static matrix::Matrix addSelfVertexLoops(matrix::Matrix &associatedMatrix) {
    for (unsigned int i = 0; i < associatedMatrix.GetColumnsCount(); i++) {
        associatedMatrix.Set(i, i, 1);
    }

    return associatedMatrix;
}

static std::vector<std::vector<unsigned int>> cluterizeMatrix(matrix::Matrix &sparseMatrix) {
    std::vector<std::vector<unsigned int>> clustersIndexes{};

    uint32_t m = sparseMatrix.GetRowsCount();
    uint32_t n = sparseMatrix.GetColumnsCount();

    std::vector<int> attractors{};

    // get attractors
//    for (uint32_t i = 0; i < m; i++) {
//        if (sparseMatrix.Get(i, i) != 0) {
//            attractors.push_back(i);
//        }
//    }

    for (uint32_t i = 0; i < m; i++) {
        std::vector<unsigned int> rowIntersect{};

        for (uint32_t j = 0; j < n; j++) {
            const auto value = sparseMatrix.Get(i, j);

            if (value > 0.001) {
                rowIntersect.push_back(j);
            }
        }

        if (!rowIntersect.empty()) {
            clustersIndexes.push_back(rowIntersect);
        }
    }

    return clustersIndexes;
}



constexpr auto MAX_ITERATION_COUNT = 1000 * 1000;

// http://www.cs.ucsb.edu/~xyan/classes/CS595D-2009winter/MCL_Presentation2.pdf
template<typename TNode, typename TEdge>
const std::vector<Cluster<TNode, TEdge>> MarkovClustering(
  const Graph <TNode, TEdge> &graph,
  uint32_t powerParam,
  uint32_t inflationParam
) {
    auto associationMatrix = createAssociatedMatrix(graph);
    associationMatrix = addSelfVertexLoops(associationMatrix);
    associationMatrix = matrix::NormalizeByColumnSum(associationMatrix);

    uint32_t iterationCount = 0;
    matrix::Matrix prevMatrix = associationMatrix;
    do {
        iterationCount++;

        if (iterationCount > MAX_ITERATION_COUNT) {
            throw std::logic_error("Graph associated matrix is not converged");
        }

        prevMatrix = associationMatrix;
        associationMatrix = matrix::Inflate(associationMatrix ^ powerParam, inflationParam);
    } while (!(prevMatrix == associationMatrix)); // iterate until steady state is reached (convergence)

    std::vector<std::vector<unsigned int>> clustersIndexes = cluterizeMatrix(associationMatrix);

    std::vector<Cluster<TNode, TEdge>> clusters{};

    for (auto i = 0; i < clustersIndexes.size(); i++) {
        std::vector<std::shared_ptr<Vertex<TNode, TEdge>>> vertices{};

        for (const auto &index : clustersIndexes[i]) {
            vertices.push_back(graph.GetVertexById(index));
        }

        clusters.push_back(Cluster<TNode, TEdge>(i, std::move(vertices)));
    }

    return clusters;
}

}
#endif
