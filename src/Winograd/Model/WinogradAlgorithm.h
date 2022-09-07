#pragma once
#include <iostream>
#include <queue>
#include <thread>
#include <vector>

#include "../SharedFiles/TypeOfRun.h"
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
    void calcRowFactor(Factor&);
    void calcColFactor(Factor&);
    bool checkSize(const Matrix&, const Matrix&);
    void calculation(Matrix&, const Factor&, const Factor&);
    void calcRowValues(Matrix&, const Factor&, const Factor&, int i);
    void addToOddMatrix(Matrix&);
    Matrix runMiltiThreadsClassic();
    Matrix runMiltiThreadsConveyor();
    Matrix runOneThread();
    Matrix runWithSetNumOfThreads();
    void calculationWithNumberOfThreads(Matrix&, const Factor&, const Factor&);
   private:
    void calcRowFactorConveyor(std::queue<double>&);
    void calcColFactorConveyor(std::queue<double>&);
    void calculationMiltiThreadsConveyor(Matrix&, std::queue<double>&, std::queue<double>&);

   public:
    void setMatrixFirst(const Matrix& other) { firstMatrix = other; }
    void setMatrixSecond(const Matrix& other) { secondMatrix = other; }
    void setNumOfThreads(int numberOfThreads) {
        if ((numberOfThreads % 4 == 0 && numberOfThreads <= std::thread::hardware_concurrency()) ||
            numberOfThreads == 2) {
            numOfThreads = numberOfThreads;
        } else
            throw std::invalid_argument("Incorrect number of threads!");
    }
    Matrix start(TypeOfRun);
    WinogradAlgorithm():threads(0),firstMatrix(1,1),secondMatrix(1,1){}
};

}  // namespace s21