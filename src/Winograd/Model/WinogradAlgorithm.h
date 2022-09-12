#pragma once
#include <iostream>
#include <queue>
#include <thread>
#include <vector>

#include "../../SharedFiles/TypeOfRun.h"
#include "Matrix.h"
namespace s21 {
using Factor = std::vector<double>;

void correctJoin(std::thread& t);

class WinogradAlgorithm {
   private:
    Matrix firstMatrix;
    Matrix secondMatrix;
    int halfSize = 0;
    int numOfThreads = 0;
    std::vector<std::thread> threads;

   private:
    bool checkSize(const Matrix&, const Matrix&);

   private:
    void calcRowFactor(Factor&);
    void calcColFactor(Factor&);
    void calculation(Matrix&, const Factor&, const Factor&);
    void calcRowValues(Matrix&, const Factor&, const Factor&, int i);
    void addToOddMatrix(Matrix&);
    Matrix runOneThread();

   private:

    Matrix runMiltiThreadsClassic();
    void calculationClassicMultiThreads(Matrix&, const Factor&, const Factor&);
   private:
    Matrix runWithSetNumOfThreads();
    void calculationWithNumberOfThreads(Matrix&, const Factor&, const Factor&);

   private:
    Matrix runMiltiThreadsConveyor();
    void calcRowFactorConveyor(std::queue<double>&);
    void calcColFactorConveyor(std::queue<double>&);
    void calculationMiltiThreadsConveyor(Matrix&, std::queue<double>&, std::queue<double>&);

   public:
    void setMatrixFirst(const Matrix& other) { firstMatrix = other; }
    void setMatrixFirstRandom(int rows, int cols) { firstMatrix.setRandom(rows, cols); }
    void setMatrixSecond(const Matrix& other) { secondMatrix = other; }
    void setMatrixSecondRandom(int rows, int cols) { secondMatrix.setRandom(rows, cols); }
    void setNumOfThreads(int numberOfThreads) {
        if ((numberOfThreads % 4 == 0 && numberOfThreads <= std::thread::hardware_concurrency()) ||
            numberOfThreads == 2) {
            numOfThreads = numberOfThreads;
        } else
            throw std::invalid_argument("Incorrect number of threads!");
    } 
    Matrix start(TypeOfRun);
    WinogradAlgorithm() : threads(0), firstMatrix(1, 1), secondMatrix(1, 1) {}
};

}  // namespace s21