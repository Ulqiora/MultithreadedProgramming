#pragma once
#include <vector>
#include <iostream>
#include "Matrix.h"
namespace s21 {
using Factor=std::vector<double>;


class WinogradAlgorithm {
   private:
    Matrix firstMatrix;
    Matrix secondMatrix;
    int halfSize=0;
    void calcRowFactor(Factor&);
    void calcColFactor(Factor&);
    bool checkSize(const Matrix&, const Matrix&);
    void calculation(Matrix&,const Factor&,const Factor&);
    void addToOddMatrix(Matrix&);
   public:
    Matrix startAlgorithm(const Matrix&, const Matrix&);
};

}  // namespace s21