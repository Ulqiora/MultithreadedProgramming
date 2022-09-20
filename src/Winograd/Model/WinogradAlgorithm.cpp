#include "WinogradAlgorithm.h"
namespace s21 {
void correctJoin(std::thread& t) {
    if (t.joinable()) t.join();
}

Matrix WinogradAlgorithm::start(TypeOfRun type) {
    if (!checkSize(firstMatrix, secondMatrix)) {
        std::cout << "Error size of matrix! " << firstMatrix.getCols() << ' ' << secondMatrix.getRows()
                  << '\n';
        throw std::invalid_argument("Error size of matrix!");
    }
    halfSize = firstMatrix.getCols() / 2;
    if (type == TypeOfRun::ONE) {
        return runOneThread();
    } else if (type == TypeOfRun::MULTI_CLASSIC) {
        return runMiltiThreadsClassic();
    } else if (type == TypeOfRun::MULTI_CONVEYOR) {
        return runMiltiThreadsConveyor();
    } else if (type == TypeOfRun::MULTI_CLASSIC_WITH_NUM) {
        return runWithSetNumOfThreads();
    }
    throw std::invalid_argument("Incorrect type of run algorithm");
}

Matrix WinogradAlgorithm::runMiltiThreadsConveyor() {
    threads.resize(3);
    Matrix result(firstMatrix.getRows(), secondMatrix.getCols());
    std::queue<double> row, col;
    threads[0] = std::move(std::thread(&WinogradAlgorithm::calcRowFactorConveyor, this, std::ref(row)));
    threads[1] = std::move(std::thread(&WinogradAlgorithm::calcColFactorConveyor, this, std::ref(col)));
    threads[2] = std::move(std::thread(&WinogradAlgorithm::calculationMiltiThreadsConveyor, this,
                                       std::ref(result), std::ref(row), std::ref(col)));
    threads[0].join(), threads[1].join(), threads[2].join();
    if ((2 * halfSize) != firstMatrix.getCols()) addToOddMatrix(result);
    return result;
}

Matrix WinogradAlgorithm::runMiltiThreadsClassic() {
    threads.resize(2);
    Matrix result(firstMatrix.getRows(), secondMatrix.getCols());
    Factor row(firstMatrix.getRows()), col(secondMatrix.getCols());
    threads[0] = std::move(std::thread(&WinogradAlgorithm::calcRowFactor, this, std::ref(row)));
    threads[1] = std::move(std::thread(&WinogradAlgorithm::calcColFactor, this, std::ref(col)));
    threads[0].join(), threads[1].join();
    calculationClassicMultiThreads(result, row, col);
    if ((2 * halfSize) != firstMatrix.getCols()) addToOddMatrix(result);
    for (int j = 0; j < firstMatrix.getRows(); ++j) {
        threads[j].join();
    }
    return result;
}

Matrix WinogradAlgorithm::runOneThread() {
    Matrix result(firstMatrix.getRows(), secondMatrix.getCols());
    Factor row(firstMatrix.getRows()), col(secondMatrix.getCols());
    calcRowFactor(row);
    calcColFactor(col);
    calculation(result, row, col);
    if ((2 * halfSize) != firstMatrix.getCols()) addToOddMatrix(result);
    return result;
}

Matrix WinogradAlgorithm::runWithSetNumOfThreads() {
    threads.resize(numOfThreads);
    Matrix result(firstMatrix.getRows(), secondMatrix.getCols());
    Factor row(firstMatrix.getRows()), col(secondMatrix.getCols());
    threads[0] = std::move(std::thread(&WinogradAlgorithm::calcRowFactor, this, std::ref(row)));
    threads[1] = std::move(std::thread(&WinogradAlgorithm::calcColFactor, this, std::ref(col)));
    threads[0].join(), threads[1].join();
    calculationWithNumberOfThreads(result, row, col);
    if ((2 * halfSize) != firstMatrix.getCols()) addToOddMatrix(result);
    return result;
}

void WinogradAlgorithm::calculationWithNumberOfThreads(Matrix& result, const Factor& row,
                                                       const Factor& col) {
    int i = 0;
    for (i = 0; i < firstMatrix.getRows(); ++i) {
        correctJoin(threads[i % (threads.size() - 1)]);
        threads[i % (threads.size() - 1)] = std::move(std::thread(
            &WinogradAlgorithm::calcRowValues, this, std::ref(result), std::ref(row), std::ref(col), i));
    }
    for (int j = 0; j < i; ++j) {
        correctJoin(threads[j % (threads.size())]);
    }
}

void WinogradAlgorithm::calculationClassicMultiThreads(Matrix& result, const Factor& row,
                                                       const Factor& col) {
    threads.resize(firstMatrix.getRows());
    for (int i = 0; i < firstMatrix.getRows(); ++i) {
        threads[i] = std::move(std::thread(&WinogradAlgorithm::calcRowValues, this, std::ref(result),
                                           std::ref(row), std::ref(col), i));
    }
}

void WinogradAlgorithm::calcRowValues(Matrix& result, const Factor& row, const Factor& col, int i) {
    for (int j = 0; j < secondMatrix.getCols(); ++j) {
        result(i, j) = -row[i] - col[j];
        for (int k = 0; k < halfSize; ++k) {
            result(i, j) += (firstMatrix(i, 2 * k) + secondMatrix(2 * k + 1, j)) *
                            (firstMatrix(i, 2 * k + 1) + secondMatrix(2 * k, j));
        }
    }
}

void WinogradAlgorithm::calculation(Matrix& result, const Factor& row, const Factor& col) {
    for (int i = 0; i < firstMatrix.getRows(); ++i) {
        for (int j = 0; j < secondMatrix.getCols(); ++j) {
            result(i, j) = -row[i] - col[j];
            for (int k = 0; k < halfSize; ++k) {
                result(i, j) += (firstMatrix(i, 2 * k) + secondMatrix(2 * k + 1, j)) *
                                (firstMatrix(i, 2 * k + 1) + secondMatrix(2 * k, j));
            }
        }
    }
}

bool WinogradAlgorithm::checkSize(const Matrix& first, const Matrix& second) {
    if (first.getCols() == second.getRows()) return true;
    return false;
}

void WinogradAlgorithm::calcRowFactor(Factor& row) {
    for (int i = 0; i < firstMatrix.getRows(); ++i) {
        row[i] = firstMatrix(i, 0) * firstMatrix(i, 1);
        for (int j = 1; j < halfSize; ++j) {
            row[i] += (firstMatrix(i, 2 * j) * firstMatrix(i, 2 * j + 1));
        }
    }
}

void WinogradAlgorithm::calcColFactor(Factor& col) {
    for (int i = 0; i < secondMatrix.getCols(); ++i) {
        col[i] = secondMatrix(0, i) * secondMatrix(1, i);
        for (int j = 1; j < halfSize; ++j) {
            col[i] += (secondMatrix(2 * j, i) * secondMatrix(2 * j + 1, i));
        }
    }
}

void WinogradAlgorithm::addToOddMatrix(Matrix& result) {
    for (int i = 0; i < result.getRows(); ++i) {
        for (int j = 0; j < result.getCols(); ++j) {
            result(i, j) +=
                (firstMatrix(i, firstMatrix.getCols() - 1) * secondMatrix(secondMatrix.getRows() - 1, j));
        }
    }
}

void WinogradAlgorithm::calcRowFactorConveyor(std::queue<double>& queueForRow) {
    double tempValue = 0.0;
    for (int i = 0; i < firstMatrix.getRows(); ++i) {
        tempValue = 0.0;
        tempValue = firstMatrix(i, 0) * firstMatrix(i, 1);
        for (int j = 1; j < halfSize; ++j) {
            tempValue += (firstMatrix(i, 2 * j) * firstMatrix(i, 2 * j + 1));
        }
        queueForRow.push(tempValue);
    }
}

void WinogradAlgorithm::calcColFactorConveyor(std::queue<double>& queueForCol) {
    double tempValue = 0.0;
    for (int i = 0; i < secondMatrix.getCols(); ++i) {
        tempValue = 0.0;
        tempValue = secondMatrix(0, i) * secondMatrix(1, i);
        for (int j = 1; j < halfSize; ++j) {
            tempValue += (secondMatrix(2 * j, i) * secondMatrix(2 * j + 1, i));
        }
        queueForCol.push(tempValue);
    }
}

void WinogradAlgorithm::calculationMiltiThreadsConveyor(Matrix& result, std::queue<double>& row,
                                                        std::queue<double>& col) {
    std::vector<double> colFactor;
    for (int i = 0; i < firstMatrix.getRows(); ++i) {
        while (row.empty()) {
        }
        for (int j = 0; j < secondMatrix.getCols(); ++j) {
            if (i == 0) {
                while (col.empty()) {
                }
                colFactor.push_back(col.front());
                col.pop();
            }
            result(i, j) -= (row.front() + colFactor[j]);
            for (int k = 0; k < halfSize; ++k) {
                result(i, j) += (firstMatrix(i, 2 * k) + secondMatrix(2 * k + 1, j)) *
                                (firstMatrix(i, 2 * k + 1) + secondMatrix(2 * k, j));
            }
        }
        row.pop();
    }
}

}  // namespace s21
