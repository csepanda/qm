#include <memory>
#include <sstream>

#include <catch2/catch.hpp>
#include <qm/algorithm/graph/HierarchicalClustering.hpp>
#include <qm/algorithm/graph/Vertex.hpp>
#include <qm/algorithm/graph/Edge.hpp>
#include <iostream>
#include "utils.hpp"

using namespace std;
using namespace qm::algorithm::graph;
using namespace tests::qm::algorithm::graph::utils;

typedef Vertex<int, int> vertex_t;
typedef Edge<int, int> edge_t;
typedef Graph<int, int> graph_t;

struct TestCase {
    const vector<vector<int>> Input;
    const vector<vector<int>> Expected;

    TestCase(
      initializer_list<vector<vector<int>>> initializer
    ) : Input{*initializer.begin()}, Expected{*(initializer.end() - 2)} {}
};

static void printClusters(vector<Cluster<int, int>> clusters) {
    for (const auto &cluster : clusters) {
        stringstream ss{};

        ss << "cluster: {";
        for (const auto &vertex : cluster.GetVertices()) {
            ss << *vertex->GetBackingNode() << ", ";
        }

        ss.seekp(-2, std::stringstream::cur);
        ss << "}";

        cout << ss.str() << endl;
    }
}

static void runTestCase(TestCase testCase) {
    const auto inputGraph = buildGraph(testCase.Input);
    const auto actual = HierarchicalClustering(inputGraph, static_cast<uint32_t>(testCase.Expected.size()));

    REQUIRE(actual.size() == testCase.Expected.size());
    for (auto i = 0; i < actual.size(); i++) {
        const auto actualCluster = actual[i];
        auto verticesExpected = testCase.Expected[i];

        REQUIRE(actualCluster.GetVertices().size() == verticesExpected.size());

        std::vector<int> verticesActual{};

        for (const auto &vertex : actualCluster.GetVertices()) {
            verticesActual.push_back(inputGraph.GetVertexId(vertex));
        }

        std::sort(verticesActual.begin(), verticesActual.end());
        std::sort(verticesExpected.begin(), verticesExpected.end());
        for (auto j = 0; j < verticesActual.size(); j++) {
            const auto &actualIndex = verticesActual[j];
            const auto expectedIndex = verticesExpected[j];

            REQUIRE(actualIndex == expectedIndex);
        }
    }
}

TEST_CASE("Hierarchical clustering verification", "[algo][graph-clustering]") {
    vector<TestCase> testCases = {
      { // only one node
        {{0}},
        {{0}}
      },
      {
/*   1-0
 *   | /
 *   2
 *   |
 *   3-5
 *    \|
 *     4
 */
        {
          {0, 1, 1, 0, 0, 0},
          {1, 0, 1, 0, 0, 0},
          {1, 1, 0, 1, 0, 0},
          {0, 0, 1, 0, 1, 1},
          {0, 0, 0, 1, 0, 1},
          {0, 0, 0, 1, 1, 0},
        },
        {
          {0, 1, 2},
          {3, 4, 5}
        }
      },
      {
/*   3---4---5
 *   |   |   |
 *   1 - 2   6
 *    \ / \
 *     0---7--8
 *          \
 *           9
 */
        {
          {1, 1, 0, 0, 0, 0, 0, 1, 0, 0},
          {1, 0, 1, 1, 0, 0, 0, 0, 0, 0},
          {1, 1, 0, 0, 1, 0, 0, 1, 0, 0},
          {0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
          {0, 0, 1, 1, 0, 1, 0, 0, 0, 0},
          {0, 0, 0, 0, 1, 0, 1, 0, 0, 0},
          {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
          {1, 0, 1, 0, 0, 0, 0, 0, 1, 1},
          {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
          {0, 0, 0, 0, 0, 0, 0, 1, 0, 0}
        },
        {

          {0, 1, 2, 3, 4},
          {5, 6},
          {7, 8, 9}
        }
      },
      {
/*  0--1--2--3
 *  |        |
 *  9        4
 *  |        |
 *  8--7--6--5
 */
        {
          {1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
          {1, 0, 1, 0, 0, 0, 0, 0, 0, 0},
          {0, 1, 0, 1, 0, 0, 0, 0, 0, 0},
          {0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
          {0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
          {0, 0, 0, 0, 1, 0, 1, 0, 0, 0},
          {0, 0, 0, 0, 0, 1, 0, 1, 0, 0},
          {0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
          {0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
          {1, 0, 0, 0, 0, 0, 0, 0, 1, 0}
        },
        {
          {0, 1},
          {2, 3, 4, 5},
          {6, 7, 8, 9}

        }
      },
      {
/*  0--1--2--3
 *  | /    \ |
 *  9        4
 *  | \    / |
 *  8--7--6--5
 */
        {
          {1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
          {1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
          {0, 1, 0, 1, 1, 0, 0, 0, 0, 0},
          {0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
          {0, 0, 1, 1, 0, 1, 1, 0, 0, 0},
          {0, 0, 0, 0, 1, 0, 1, 0, 0, 0},
          {0, 0, 0, 0, 1, 1, 0, 1, 0, 0},
          {0, 0, 0, 0, 0, 0, 1, 0, 1, 1},
          {0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
          {1, 1, 0, 0, 0, 0, 0, 1, 1, 0}
        },
        {
          {2, 3, 4, 5, 6},
          {0, 1, 7, 8, 9}
        }
      },
      {
/* 0-1-2-3-4-5-6 */
        {
          {0, 1, 0, 0, 0, 0, 0},
          {1, 0, 1, 0, 0, 0, 0},
          {0, 1, 0, 1, 0, 0, 0},
          {0, 0, 1, 0, 1, 0, 0},
          {0, 0, 0, 1, 0, 1, 0},
          {0, 0, 0, 0, 1, 0, 1},
          {0, 0, 0, 0, 0, 1, 0}
        },
        {
          {0, 1, 2},
          {3, 4, 5, 6}
        }
      }
    };

    for (const auto &testCase : testCases) {
        runTestCase(testCase);
    }
}

