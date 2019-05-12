#include <memory>
#include <sstream>

#include <catch2/catch.hpp>
#include <qm/algorithm/graph/MarkovClustering.hpp>
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
    ) : Input{*initializer.begin()}, Expected{*(initializer.end() - 1)} {}
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
    const auto actual = MarkovClustering(inputGraph, 2, 2);

    REQUIRE(actual.size() == testCase.Expected.size());
    for (auto i = 0; i < actual.size(); i++) {
        const auto actualCluster = actual[i];
        const auto expectedCluster = testCase.Expected[i];
        const auto &vertices = actualCluster.GetVertices();

        REQUIRE(vertices.size() == expectedCluster.size());
        for (auto j = 0; j < vertices.size(); j++) {
            const auto &actualVertex = vertices[j];
            const auto index = inputGraph.GetVertexId(actualVertex);

            REQUIRE(index == expectedCluster[j]);
        }
    }
}

TEST_CASE("MarkovClustering verification", "[algo][graph-clustering]") {
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

         {4, 5, 6},
          {0, 1, 2, 3, 7, 8, 9}
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
         {0, 1, 2},
          {3, 4, 5},
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
         {0, 1, 2, 3},
          {3, 4, 5, 6}
        }
      }
    };

    for (const auto &testCase : testCases) {
        runTestCase(testCase);
    }
}

