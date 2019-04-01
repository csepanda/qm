#include <cmath>
#include <qm/algorithm/matrix/Normalization.hpp>

namespace qm::algorithm::matrix {

Matrix NormalizeByColumnSum(const Matrix &matrix) {
    const unsigned int m = matrix.GetRowsCount();
    const unsigned int n = matrix.GetColumnsCount();

    Matrix normalized{m, n};

    for (unsigned int j = 0; j < n; j++) {
        double sum = 0;

        for (unsigned int i = 0; i < m; i++) {
            sum += matrix.Get(i, j);
        }

        for (unsigned int i = 0; i < m; i++) {
            const auto currentValue = matrix.Get(i, j);

            normalized.Set(i, j, currentValue / sum);
        }
    }

    return normalized;
}

Matrix Inflate(const Matrix &matrix, unsigned int inflationParameter) {
    const unsigned int m = matrix.GetRowsCount();
    const unsigned int n = matrix.GetColumnsCount();

    Matrix powered{m, n};

    for (unsigned int i = 0; i < m; i++) {
        for (unsigned int j = 0; j < n; j++) {
            powered.Set(i, j, pow(matrix.Get(i, j), inflationParameter));
        }
    }

    return NormalizeByColumnSum(powered);
}

}
