#include "SquareMatrix.h"

namespace s21 {
void SquareMatrix::allocateMemory() {
    matrixData = new double*[_size];
    for (int i = 0; i < _size; ++i) {
        matrixData[i] = new double[_size]();
    }
}
void SquareMatrix::freeMemory() {
    if (!matrixData) {
        for (int i = 0; i < _size; ++i) {
            delete[] matrixData[i];
        }
        delete[] matrixData;
    }
}

SquareMatrix::SquareMatrix() {
    _size = 0;
    matrixData = nullptr;
}

SquareMatrix::SquareMatrix(const SquareMatrix& other) : _size(other._size) {
    allocateMemory();
    copyMatrixData(other);
}

SquareMatrix::SquareMatrix(int newSize) : _size(newSize), matrixData(nullptr) {
    if (_size < 1) throw std::invalid_argument("alo");
    allocateMemory();
}

void SquareMatrix::setSize(int newSize) {
    if (newSize < 1) throw std::invalid_argument("first argument < 1");
    if (newSize == _size) return;
    SquareMatrix copy(*this);
    freeMemory();
    _size = newSize;
    allocateMemory();
    copyMatrixData(copy);
}

void SquareMatrix::copyMatrixData(const SquareMatrix& other) {
    int minimumSize = _size < other._size ? _size : other._size;
    for (int i = 0; i < minimumSize; ++i) {
        for (int j = 0; j < minimumSize; ++j) {
            matrixData[i][j] = other.matrixData[i][j];
        }
    }
}

const SquareMatrix& SquareMatrix::operator=(const SquareMatrix& other) {
    if (&other == this) return other;
    if (!(this->_size == other._size)) {
        freeMemory();
        _size = other._size;
        allocateMemory();
    }
    copyMatrixData(other);
    return other;
}

void SquareMatrix::loadMatrix(std::ifstream& file) {
    std::string temp = "";
    file >> temp;
    if (isdigit(temp[0]) && temp[0] != '-')
        setSize(std::stoi(temp));
    else
        throw std::invalid_argument(" fdsafdsfasfas");
    for (int i = 0; i < _size; i++) {
        for (int j = 0; j < _size; j++) {
            file >> temp;
            if (isdigit(temp[0]) || (isdigit(temp[1]) && temp[0] == '-'))
                matrixData[i][j] = std::stod(temp);
            else
                throw std::invalid_argument(" file error");
        }
    }
}

void SquareMatrix::setValueForAll(double value) {
    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            matrixData[i][j] = value;
        }
    }
}

bool SquareMatrix::operator==(const SquareMatrix& other) {
    if (_size != other._size) return false;
    for (int i = 0; i < _size; i++) {
        for (int j = 0; j < _size; ++j) {
            if (std::fabs(matrixData[i][j] - other.matrixData[i][j]) >
                std::numeric_limits<double>::epsilon())
                return false;
        }
    }
    return true;
}

void SquareMatrix::mul_number(const double num) {
    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            matrixData[i][j] *= num;
        }
    }
}

SquareMatrix& SquareMatrix::operator*=(const double value) {
    mul_number(value);
    return *this;
}

}  // namespace s21