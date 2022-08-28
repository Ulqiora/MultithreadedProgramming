#include "Matrix.h"

#include <cmath>
#include <stdexcept>
namespace s21 {
Matrix::Matrix() { allocateMemory(3, 3); }

Matrix::Matrix(int rows, int cols) {
    if (rows > 0 && cols > 0) {
        allocateMemory(rows, cols);
    } else {
        throw std::out_of_range("Incorrect input, matrix should have both sizes > 0");
    }
}

Matrix::Matrix(const Matrix& other) : Matrix(other.rows, other.cols) { copyMatrix(other.matrix); }

Matrix::Matrix(Matrix&& other) {
    rows = other.rows;
    cols = other.cols;
    matrix = other.matrix;
    other.matrix = nullptr;
}

Matrix::~Matrix() {
    if (matrix) {
        freeMemory();
    }
}

bool Matrix::eq_matrix(const Matrix& other) const {
    bool result = true;
    if (isEqualSizes(other)) {
        for (int i = 0; i < rows && result; i++) {
            for (int j = 0; j < cols && result; j++) {
                if (fabs(matrix[i][j] - other.matrix[i][j]) > 1e-7) result = false;
            }
        }
    } else {
        result = false;
    }
    return result;
}

void Matrix::sum_matrix(const Matrix& other) {
    if (isEqualSizes(other)) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = matrix[i][j] + other.matrix[i][j];
            }
        }
    } else {
        throw std::invalid_argument("Invalid argument, matrices must be equal sizes");
    }
}

void Matrix::sub_matrix(const Matrix& other) {
    if (isEqualSizes(other)) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = matrix[i][j] - other.matrix[i][j];
            }
        }
    } else {
        throw std::invalid_argument("Invalid argument, matrices must be equal sizes");
    }
}

void Matrix::mul_number(const double num) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] *= num;
        }
    }
}

void Matrix::mul_matrix(const Matrix& other) {
    if (cols == other.rows) {
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                for (int c = 0; c < cols; c++) result.matrix[i][j] += matrix[i][c] * other.matrix[c][j];
            }
        }
        *this = result;
    } else {
        throw std::invalid_argument(
            "Invalid argument, number of cols of the first matrix must be equal to number of rows of the "
            "second matrix");
    }
}

int Matrix::getRows() const { return rows; }

int Matrix::getCols() const { return cols; }

Matrix Matrix::operator+(const Matrix& other) const {
    Matrix result = *this;
    result.sum_matrix(other);
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    Matrix result = *this;
    result.sub_matrix(other);
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    Matrix result = *this;
    result.mul_matrix(other);
    return result;
}

Matrix Matrix::operator*(const double num) const {
    Matrix result = *this;
    result.mul_number(num);
    return result;
}

Matrix operator*(double num, const Matrix& other) {
    Matrix result = other;
    result.mul_number(num);
    return result;
}

bool Matrix::operator==(const Matrix& other) const { return eq_matrix(other); }

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        freeMemory();
        allocateMemory(other.rows, other.cols);
        copyMatrix(other.matrix);
    }
    return *this;
}

Matrix Matrix::operator+=(const Matrix& other) {
    sum_matrix(other);
    return *this;
}

Matrix Matrix::operator-=(const Matrix& other) {
    sub_matrix(other);
    return *this;
}

Matrix Matrix::operator*=(const Matrix& other) {
    mul_matrix(other);
    return *this;
}

Matrix Matrix::operator*=(const double num) {
    mul_number(num);
    return *this;
}

const double& Matrix::operator()(int i, int j) const {
    if (i >= 0 && i < rows && j >= 0 && j < cols) {
        return matrix[i][j];
    } else {
        throw std::out_of_range("Incorrect input, index out of matrix sizes");
    }
}

double& Matrix::operator()(int i, int j) {
    if (i >= 0 && i < rows && j >= 0 && j < cols) {
        return matrix[i][j];
    } else {
        throw std::out_of_range("Incorrect input, index out of matrix sizes");
    }
}

inline bool Matrix::isEqualSizes(const Matrix& other) const {
    return (rows == other.rows && cols == other.cols);
}

inline bool Matrix::isSquareMatrix() const { return (rows == cols); }

void Matrix::allocateMemory(int rows, int cols) {
    rows = rows;
    cols = cols;
    matrix = new double*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new double[cols]();
    }
}

void Matrix::freeMemory() {
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void Matrix::copyMatrix(double** other_matrix) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = other_matrix[i][j];
        }
    }
}
}  // namespace s21
