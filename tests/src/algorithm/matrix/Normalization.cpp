#include <catch2/catch.hpp>
#include <qm/algorithm/matrix/Normalization.hpp>

using namespace qm::algorithm::matrix;

const auto epsilon = 0.0001;

TEST_CASE("NormalizeBySum test", "[algo]") {
    const Matrix input = {
      {1, 1, 1},
      {1, 0, 1},
      {0, 0, 1},
      {0, 0, 1}
    };

    const Matrix expected = {
      {0.5, 1, 0.25},
      {0.5, 0, 0.25},
      {0,   0, 0.25},
      {0,   0, 0.25}
    };

    const Matrix actual = NormalizeByColumnSum(input);

    REQUIRE(actual == expected);
}

TEST_CASE("Inflate test // square", "[algo]") {
    const Matrix input = {
      {0,      1, 1},
      {0.5,    0, 1},
      {1. / 6, 0, 1},
      {1. / 3, 0, 1}
    };

    const Matrix expected = {
      {0,       1, 0.25},
      {9. / 14, 0, 0.25},
      {1. / 14, 0, 0.25},
      {4. / 14, 0, 0.25}
    };

    const Matrix actual = Inflate(input, 2);

    REQUIRE(actual == expected);

}
