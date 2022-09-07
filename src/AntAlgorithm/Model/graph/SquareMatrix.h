#pragma once
#include <cmath>
#include <exception>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
namespace s21 {
class SquareMatrix {
 private:
  int _size;
  double** matrixData;
  void allocateMemory();
  void freeMemory();
  void copyMatrixData(const SquareMatrix& other);

 public:
  SquareMatrix(int newSize);
  SquareMatrix();
  SquareMatrix(const SquareMatrix& other);
  double& operator()(int i, int j) const { return matrixData[i][j]; }
  ~SquareMatrix() { freeMemory(); }
  int size() const { return _size; }
  const SquareMatrix& operator=(const SquareMatrix& other);
  bool operator==(const SquareMatrix& other);
  void setSize(int newNumOfRows);
  void loadMatrix(std::ifstream& file);
  void setValueForAll(double value);
  void mul_number(const double num);
  SquareMatrix& operator*=(const double value);
};
}  // namespace s21