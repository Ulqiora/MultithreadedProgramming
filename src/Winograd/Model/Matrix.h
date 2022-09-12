#pragma once
#include <iostream>
namespace s21 {

class Matrix {
   private:
    int _rows, _cols;
    double** _matrix;

   public:
    Matrix();
    Matrix(int rows, int cols);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other);
    ~Matrix();
    bool eq_matrix(const Matrix& other) const;
    void sum_matrix(const Matrix& other);
    void sub_matrix(const Matrix& other);
    void mul_number(const double num);
    void mul_matrix(const Matrix& other);

    int getRows() const;
    int getCols() const;
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(const double num) const;
    friend Matrix operator*(const double num, const Matrix& other);
    bool operator==(const Matrix& other) const;
    Matrix& operator=(const Matrix& other);
    Matrix operator+=(const Matrix& other);
    Matrix operator-=(const Matrix& other);
    Matrix operator*=(const Matrix& other);
    Matrix operator*=(const double num);
    const double& operator()(int i, int j) const;
    double& operator()(int i, int j);
    void setRandom(int rows, int cols);
    void print() {
            for (int i = 0; i < _rows; i++) {
                for (int j = 0; j < _cols; j++) {
                    std::cout << _matrix[i][j] << '\t';
                }
                std::cout << std::endl;
            }
    }

   private:
    inline bool isEqualSizes(const Matrix& other) const;
    inline bool isSquareMatrix() const;
    void newMatrix(int rows, int cols);
    void destroyMatrix();
    void copyMatrix(double** other_matrix);
};

Matrix operator*(double num, const Matrix& other);
}  // namespace s21