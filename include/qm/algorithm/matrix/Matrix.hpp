#ifndef QM_ALGORITHM_MATRIX_MATRIX_HPP
#define QM_ALGORITHM_MATRIX_MATRIX_HPP

#include <vector>

namespace qm::algorithm::matrix {

class Matrix {
    unsigned int m_rowsCount, m_columnsCount;
    std::vector<std::vector<double>> m_data{};
public:
    Matrix(unsigned int m, unsigned int n);

    Matrix(std::initializer_list<std::vector<double>> list);

    double Get(unsigned int m, unsigned int n) const;

    void Set(unsigned int i, unsigned int j, double value);

    unsigned int GetRowsCount() const;

    unsigned int GetColumnsCount() const;

    std::vector<double> GetRow(unsigned int m) const;

    std::vector<double> GetColumn(unsigned int n) const;

    Matrix operator*(const Matrix &) const;

    Matrix operator^(int power) const;

    bool operator==(const Matrix &) const;

private:
    void zeroReset(unsigned int m, unsigned int n);
};
}

#endif //QM_ALGORITHM_MATRIX_MATRIX_HPP
