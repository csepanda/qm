#ifndef QM_ALGORITHM_MATRIX_UTILS_HPP
#define QM_ALGORITHM_MATRIX_UTILS_HPP

#include "Matrix.hpp"

namespace qm::algorithm::matrix {
Matrix NormalizeByColumnSum(const Matrix &m);

Matrix Inflate(const Matrix &m, unsigned int inflationParameter);
}

#endif //QM_ALGORITHM_MATRIX_UTILS_HPP
