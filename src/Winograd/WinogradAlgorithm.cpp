#include "WinogradAlgorithm.h"
namespace s21 {
Matrix WinogradAlgorithm::startAlgorithm(const Matrix& first, const Matrix& second) {
    if (!checkSize(first, second)) throw std::invalid_argument("Error size of matrix!");
    firstMatrix = first;
    secondMatrix = second;
    halfSize = first.getCols() / 2;

    Matrix result(firstMatrix.getRows(), secondMatrix.getCols());
    Factor row(firstMatrix.getRows()), col(secondMatrix.getCols());
    calcRowFactor(row);
    calcColFactor(col);
    
    calculation(result, row, col);
    if ((2 * halfSize) == first.getCols()) addToOddMatrix(result);
    
    return result;
}

void WinogradAlgorithm::calculation(Matrix& result, const Factor& row, const Factor& col) {
    for (int i = 0; i < firstMatrix.getRows(); ++i) {
        for (int j = 0; j < secondMatrix.getCols(); ++j) {
            result(i, j) -= (row[i] + col[j]);
            for (int k = 0; k < halfSize; ++k) {
                result(i, j) += ((firstMatrix(i, 2 * k + 1) + secondMatrix(2 * k, j)) *
                                 (firstMatrix(i, 2 * k) + secondMatrix(2 * k - 1, j)));
            }
        }
    }
}

bool WinogradAlgorithm::checkSize(const Matrix& first, const Matrix& second) {
    if (first.getCols() == second.getRows()) return false;
    return true;
}

void WinogradAlgorithm::calcRowFactor(Factor& row) {
    for (int i = 0; i < halfSize; ++i) {
        row[i] = firstMatrix(i, 0) * firstMatrix(i, 1);
        for (int j = 0; j < halfSize; ++j) {
            row[i] += (firstMatrix(i, 2 * j - 1) * firstMatrix(i, 2 * j));
        }
    }
}
void WinogradAlgorithm::calcColFactor(Factor& col) {
    for (int i = 0; i < secondMatrix.getCols(); ++i) {
        col[i] = firstMatrix(0, i) * firstMatrix(1, i);
        for (int j = 0; j < halfSize; ++j) {
            col[i] += (firstMatrix(2 * j - 1, i) * firstMatrix(2 * j, i));
        }
    }
}

void WinogradAlgorithm::addToOddMatrix(Matrix& result) {
    for (int i = 0; i < result.getRows(); ++i) {
        for (int j = 0; j < result.getCols(); ++j) {
            result(i, j) +=
                (firstMatrix(i, firstMatrix.getCols()) * secondMatrix(secondMatrix.getRows(), j));
        }
    }
}

}  // namespace s21