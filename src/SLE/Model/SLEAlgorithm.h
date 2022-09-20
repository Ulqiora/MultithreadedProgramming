#pragma once

#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "../../SharedFiles/Matrix.h"
#include "../../SharedFiles/TypeOfRun.h"
#include "SLEResult.h"

namespace s21 {

class SLEAlgorithm {
 private:
    Matrix data_, dataOld;
    SLEResult result;
    int mSize = 0;

 public:
    SLEAlgorithm() {}
    void setMatrix(const Matrix& m);
    SLEResult start(TypeOfRun);
    const std::vector<double>& getAnswer();
    void printAnswer();
    void setFromFile(std::string path);
    void createMatrix();

 private:
    void solveGauss(TypeOfRun);
    void oneThread(int row, int col);
    void forwardStep();
    void backStep();
    void findAnswers(int index);
};

}  // namespace s21
