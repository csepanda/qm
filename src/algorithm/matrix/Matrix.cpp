#include <cmath>
#include <stdexcept>
#include <qm/algorithm/matrix/Matrix.hpp>

namespace qm::algorithm::matrix {

Matrix::Matrix(unsigned int m, unsigned int n) {
    zeroReset(m, n);
}

Matrix::Matrix(std::initializer_list<std::vector<double>> list) : m_data{list} {
    auto rowsCount = list.size();
    auto colsCount = -1;

    for (const auto &row : list) {
        if (colsCount == -1) {
            colsCount = static_cast<int>(row.size());
        }

        if (colsCount != row.size()) {
            throw std::logic_error("Columns count in initializer list is not equal");
        }
    }

    if (colsCount == -1) {
        colsCount = 0;
    }

    m_rowsCount = static_cast<unsigned int>(rowsCount);
    m_columnsCount = static_cast<unsigned int>(colsCount);
}

void Matrix::zeroReset(unsigned int m, unsigned int n) {
    m_rowsCount = m;
    m_columnsCount = n;

    for (auto i = 0; i < m; i++) {
        m_data.emplace_back(n, 0);
    }
}

double Matrix::Get(unsigned int m, unsigned int n) const {
    return m_data[m][n];
}

void Matrix::Set(unsigned int i, unsigned int j, double value) {
    m_data[i][j] = value;
}

Matrix Matrix::operator*(const Matrix &other) const {
    if (other.m_rowsCount != m_columnsCount) {
        throw std::logic_error("Cannot multiply matrix where m2 != n1");
    }

    const unsigned int m = m_rowsCount;
    const unsigned int n = other.m_columnsCount;
    const unsigned int K = m_columnsCount;

    Matrix newMatrix(m, n);

    for (auto i = 0; i < m; i++) {
        for (auto j = 0; j < n; j++) {
            for (auto k = 0; k < K; k++) {
                newMatrix.m_data[i][j] += m_data[i][k] * other.m_data[k][j];
            }
        }
    }

    return newMatrix;
}

Matrix Matrix::operator^(int power) const {
    if (power < 0) {
        throw std::logic_error("negative power is not supported");
    }

    Matrix newMatrix = *this;

    while (0 < --power) {
        newMatrix = newMatrix * *this;
    }

    return newMatrix;
}

std::vector<double> Matrix::GetRow(unsigned int m) const {
    return m_data[m];
}

std::vector<double> Matrix::GetColumn(unsigned int n) const {
    std::vector<double> column(m_rowsCount, 0);

    for (auto i = 0; i < m_rowsCount; i++) {
        column.push_back(m_data[i][n]);
    }

    return column;
}

unsigned int Matrix::GetRowsCount() const {
    return m_rowsCount;
}

unsigned int Matrix::GetColumnsCount() const {
    return m_columnsCount;
}

inline static double epsilon = 0.0000000001;
bool Matrix::operator==(const Matrix &other) const {
    if (this->m_columnsCount != other.m_columnsCount || this->m_rowsCount != other.m_rowsCount) {
        return false;
    }

    for (uint32_t i = 0; i < m_rowsCount; i++) {
        for (uint32_t j = 0; j < m_columnsCount; j++) {
            if (fabs(m_data[i][j] - other.m_data[i][j]) > epsilon) {
                return false;
            }
        }
    }

    return true;
}

}
