#pragma once

#include <iostream>
#include <fstream>
#include <exception>
#include <vector>
#include <string>
#include <thread>

#include "../../SharedFiles/Matrix.h"
#include "../../SharedFiles/TypeOfRun.h"

namespace s21 {

class SLEAlgorithm {
 private:
  Matrix data_, dataOld;
  std::vector<double> answer;
  int mSize = 0;

 public:
  SLEAlgorithm() {}
  void setMatrix(const Matrix& m);
  void start(TypeOfRun);
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