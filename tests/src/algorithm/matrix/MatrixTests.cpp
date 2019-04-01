#include <catch2/catch.hpp>

#include <qm/algorithm/matrix/Matrix.hpp>

using namespace qm::algorithm::matrix;

// someday these tests will be improved and cover more cases, but not today

TEST_CASE("simple constructor test", "[algo]") {
    const uint32_t m = 32, n = 30;

    Matrix actual(m, n);

    for (auto i = 0; i < m; ++i) {
        for (auto j = 0; j < n; ++j) {
            REQUIRE(actual.Get(i, j) == 0);
        }
    }
}

TEST_CASE("initialize list test", "[algo]") {
    std::initializer_list<std::vector<double>> initializerList = {
      {1, 2, 3, 4, 5},
      {5, 4, 3, 2, 1},
      {0, 1, 0, 0, 1}
    };

    std::vector<std::vector<double>> expected = initializerList;

    Matrix actual = initializerList;

    for (auto i = 0; i < 3; ++i) {
        for (auto j = 0; j < 5; ++j) {
            REQUIRE(actual.Get(i, j) == expected[i][j]);
        }
    }
}

TEST_CASE("matrix multiplication test", "[algo]") {
    Matrix a = {
      {1, 0},
      {0, 1},
      {1, 1}
    }, b = {
      {1, 2, 1},
      {0, 1, 2}
    };

    Matrix expected = {
      {1, 2, 1},
      {0, 1, 2},
      {1, 3, 3}
    };

    Matrix actual = a * b;

    REQUIRE(expected == actual);
}

TEST_CASE("matrix power test // square", "[algo]") {
    Matrix input = {
      {-1, 2, -5},
      {3, 4, 1},
      {0, 1, 2}
    };

    Matrix expected = {
      {7, 1, -3},
      {9, 23, -9},
      {3, 6, 5}
    };

    Matrix actual = input ^ 2;


    REQUIRE(expected == actual);
}

TEST_CASE("matrix power test // qube", "[algo]") {
    Matrix input = {
      {0, -1},
      {3, 2}
    };

    Matrix expected = {
      {-6, -1},
      {3, -4}
    };

    Matrix actual = input ^ 3;

    REQUIRE(expected == actual);
}
