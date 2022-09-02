#include "Matrix.h"

#include <cmath>
#include <stdexcept>
#include <random>
namespace s21 {

void Matrix::setRandom(int rows, int cols)
{
    if (!(rows > 0 && cols > 0)) std::out_of_range("Incorrect input, matrix should have both sizes > 0");
    destroyMatrix();
    newMatrix(rows,cols);
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_real_distribution<double> dist(-100, 100);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            _matrix[i][j] = dist(engine);
        }
    }
}

// Constructors
Matrix::Matrix() { newMatrix(3, 3); }

Matrix::Matrix(int rows, int cols) {
    if (rows > 0 && cols > 0) {
        newMatrix(rows, cols);
    } else {
        throw std::out_of_range("Incorrect input, matrix should have both sizes > 0");
    }
}

Matrix::Matrix(const Matrix& other) : Matrix(other._rows, other._cols) {
    copyMatrix(other._matrix);
}

Matrix::Matrix(Matrix&& other) {
    _rows = other._rows;
    _cols = other._cols;
    _matrix = other._matrix;
    other._matrix = nullptr;
}

// Destructor
Matrix::~Matrix() {
    if (_matrix) {
        destroyMatrix();
    }
}

// Methods
bool Matrix::eq_matrix(const Matrix& other) const {
    bool result = true;
    if (isEqualSizes(other)) {
        for (int i = 0; i < _rows && result; i++) {
            for (int j = 0; j < _cols && result; j++) {
                if (fabs(_matrix[i][j] - other._matrix[i][j]) > 1e-7) result = false;
            }
        }
    } else {
        result = false;
    }
    return result;
}

void Matrix::sum_matrix(const Matrix& other) {
    if (isEqualSizes(other)) {
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < _cols; j++) {
                _matrix[i][j] = _matrix[i][j] + other._matrix[i][j];
            }
        }
    } else {
        throw std::invalid_argument("Invalid argument, matrices must be equal sizes");
    }
}

void Matrix::sub_matrix(const Matrix& other) {
    if (isEqualSizes(other)) {
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < _cols; j++) {
                _matrix[i][j] = _matrix[i][j] - other._matrix[i][j];
            }
        }
    } else {
        throw std::invalid_argument("Invalid argument, matrices must be equal sizes");
    }
}

void Matrix::mul_number(const double num) {
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            _matrix[i][j] *= num;
        }
    }
}

void Matrix::mul_matrix(const Matrix& other) {
    if (_cols == other._rows) {
        Matrix result(_rows, other._cols);
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < other._cols; j++) {
                for (int c = 0; c < _cols; c++) result._matrix[i][j] += _matrix[i][c] * other._matrix[c][j];
            }
        }
        *this = result;
    } else {
        throw std::invalid_argument(
            "Invalid argument, number of cols of the first matrix must be equal to number of rows of the "
            "second matrix");
    }
}

int Matrix::getRows() const { return _rows; }

int Matrix::getCols() const { return _cols; }

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
        destroyMatrix();
        newMatrix(other._rows, other._cols);
        copyMatrix(other._matrix);
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
    if (i >= 0 && i < _rows && j >= 0 && j < _cols) {
        return _matrix[i][j];
    } else {
        throw std::out_of_range("Incorrect input, index out of matrix sizes");
    }
}

double& Matrix::operator()(int i, int j) {
    if (i >= 0 && i < _rows && j >= 0 && j < _cols) {
        return _matrix[i][j];
    } else {
        throw std::out_of_range("Incorrect input, index out of matrix sizes");
    }
}

inline bool Matrix::isEqualSizes(const Matrix& other) const {
    return (_rows == other._rows && _cols == other._cols);
}

inline bool Matrix::isSquareMatrix() const { return (_rows == _cols); }

void Matrix::newMatrix(int rows, int cols) {
    _rows = rows;
    _cols = cols;
    _matrix = new double*[_rows];
    for (int i = 0; i < _rows; i++) {
        _matrix[i] = new double[_cols]();
    }
}

void Matrix::destroyMatrix() {
    for (int i = 0; i < _rows; i++) {
        delete[] _matrix[i];
    }
    delete[] _matrix;
}

void Matrix::copyMatrix(double** other_matrix) {
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            _matrix[i][j] = other_matrix[i][j];
        }
    }
}

}  // namespace s21
