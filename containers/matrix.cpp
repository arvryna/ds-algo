#ifndef MATRIX_SRC_MATRIX_H
#define MATRIX_SRC_MATRIX_H

#include <algorithm>
#include <iostream>

template <typename T, size_t _row, size_t _col>

class Matrix {
private:
    T** _head;
    using matrix_minor = Matrix<T, std::max<size_t>(_row - 1, 1), std::max<size_t>(_col - 1, 1)>;

public:
    Matrix() {
        _head = new T*[_row];
        for (int i = 0; i < _row; i++) {
            _head[i] = new T[_col];
            for (int j = 0; j < _col; j++) {
                _head[i][j] = 0;
            }
        }
    }

    Matrix(const T& num) {
        _head = new T*[_row];
        for (int i = 0; i < _row; i++) {
            _head[i] = new T[_col];
            for (int j = 0; j < _col; j++) {
                _head[i][j] = num;
            }
        }
    }

    // copy constructor (create new data and copy other data)
    Matrix(const Matrix& other) {
        _head = new T*[_row];
        for (int i = 0; i < _row; i++) {
            _head[i] = new T[_col];
            for (int j = 0; j < _col; j++) {
                _head[i][j] = other._head[i][j];
            }
        }
    }

    Matrix& operator=(const Matrix& other) {
        for (int i = 0; i < _row; i++) {
            for (int j = 0; j < _col; j++) {
                _head[i][j] = other._head[i][j];
            }
        }
        return *this;
    }

    Matrix<T, _col, _row> transposed() const {
        Matrix<T, _col, _row> m;
        for (int i = 0; i < _row; i++) {
            for (int j = 0; j < _col; j++) {
                m.at(j, i) = at(i, j);
            }
        }
        return m;
    }

    T det() const {
        T res = 0;
        T** arr = _head;
        if (_row == 2 & _col == 2) {
            int x = (arr[0][0] * arr[1][1]) - (arr[1][0] * arr[0][1]);
            return x;
        } else {
            matrix_minor m;
            for (int avoid_col = 0; avoid_col < _col; avoid_col++) {
                int i = 0;
                int j = 0;
                for (int c = 0; c < _col; c++) {
                    i = 0;
                    for (int r = 0; r < _row; r++) {
                        if (c != avoid_col && r != 0) {
                            m.at(i, j) = arr[r][c];
                            i++;
                        }
                    }
                    if (c != avoid_col)
                        j++;
                }
                int val = m.det();
                if (avoid_col % 2 == 0) {
                    res = res + (arr[0][avoid_col] * val);
                } else {
                    res = res - (arr[0][avoid_col] * val);
                }
            }
        }
        return res;
    }

    T trace() const {
        T res = 0;
        for (int i = 0; i < _row; i++) {
            res += _head[i][i];
        }
        return res;
    }

    // Return reference of an element(i,j) and also allow it to but modified by the caller
    T& at(const size_t& i, const size_t& j) {
        return _head[i][j];
    }

    // Return CONST reference of an element(i,j) which can by only READ by caller
    // This is just a overloaded function of another func /at(i,j) wrote in this project
    const T& at(const size_t& i, const size_t& j) const {
        return _head[i][j];
    }

    void ToString() const {
        for (int i = 0; i < _row; i++) {
            printf("%d: ", i);
            for (int j = 0; j < _col; j++) {
                printf("%d ", _head[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }

    ~Matrix() {
        for (int i = 0; i < _row; i++) {
            delete[] _head[i];
        }
        delete[] _head;
    }

    Matrix& operator+=(const Matrix& second) {
        for (int i = 0; i < _row; i++) {
            for (int j = 0; j < _col; j++) {
                int x = _head[i][j];
                int y = second._head[i][j];
                _head[i][j] = x + y;
            }
        }
        return *this;
    }

    Matrix& operator-=(const Matrix& second) {
        for (int i = 0; i < _row; i++) {
            for (int j = 0; j < _col; j++) {
                int x = _head[i][j];
                int y = second._head[i][j];
                _head[i][j] = x - y;
            }
        }
        return *this;
    }

    // this function is the result of mul with +1, so no change in res
    const Matrix operator+() const {
        Matrix cpy(*this);
        return cpy;
    }

    Matrix operator+(const int scalar) const {
        Matrix cpy(*this);
        for (int i = 0; i < _row; i++) {
            for (int j = 0; j < _col; j++) {
                cpy._head[i][j] = cpy._head[i][j] + scalar;
            }
        }
        return cpy;
    }

    Matrix operator+(const Matrix& other) const {
        Matrix cpy(*this);
        for (int i = 0; i < _row; i++) {
            for (int j = 0; j < _col; j++) {
                cpy._head[i][j] = cpy._head[i][j] + other._head[i][j];
            }
        }
        return cpy;
    }

    // changing sign of operator
    const Matrix operator-() const {
        Matrix cpy(*this);
        for (int i = 0; i < _row; i++) {
            for (int j = 0; j < _col; j++) {
                cpy._head[i][j] = cpy._head[i][j] * (-1);
            }
        }
        return cpy;
    }

    Matrix operator-(const int scalar) const {
        Matrix cpy(*this);
        for (int i = 0; i < _row; i++) {
            for (int j = 0; j < _col; j++) {
                cpy._head[i][j] = cpy._head[i][j] - scalar;
            }
        }
        return cpy;
    }

    Matrix operator-(const Matrix& other) const {
        Matrix cpy(*this);
        for (int i = 0; i < _row; i++) {
            for (int j = 0; j < _col; j++) {
                cpy._head[i][j] = cpy._head[i][j] - other._head[i][j];
            }
        }
        return cpy;
    }

    // ****** Multiplication ********

    Matrix operator*(const int scalar) const {
        Matrix cpy(*this);
        for (int i = 0; i < _row; i++) {
            for (int j = 0; j < _col; j++) {
                cpy._head[i][j] = cpy._head[i][j] * scalar;
            }
        }
        return cpy;
    }

    Matrix operator*(const Matrix& second) const {
        Matrix cpy(*this);
        return cpy;
    }

    Matrix& operator*=(const int scalar) {
        for (int i = 0; i < _row; i++) {
            for (int j = 0; j < _col; j++) {
                _head[i][j] = _head[i][j] * scalar;
            }
        }
        return *this;
    }

    Matrix& operator*=(const Matrix& second) {
        return *this;
    }

    template <typename K, size_t _r, size_t _c>
    Matrix<K, _r, _c>& operator*=(const Matrix<K, _r, _c>& second) {
        return *this;
    }

private:
    template <typename K, size_t _r, size_t _c>
    friend bool operator==(const Matrix<K, _r, _c>& first, const Matrix<K, _r, _c>& second);
};

template <typename T, size_t _r, size_t _c>
bool operator!=(const Matrix<T, _r, _c>& first, const Matrix<T, _r, _c>& second) {
    return !(first == second);
}

template <typename K, size_t _r, size_t _c>
bool operator==(const Matrix<K, _r, _c>& first, const Matrix<K, _r, _c>& second) {
    for (int i = 0; i < _r; i++) {
        for (int j = 0; j < _c; j++) {
            int x = first._head[i][j];
            int y = second._head[i][j];
            if (x != y) {
                return false;
            }
        }
    }
    return true;
}

template <typename K, size_t _r, size_t _c>
Matrix<K, _r, _c> operator*(const int scalar, const Matrix<K, _r, _c>& other) {
    Matrix cpy(other);
    for (int i = 0; i < _r; i++) {
        for (int j = 0; j < _c; j++) {
            cpy.at(i, j) = cpy.at(i, j) * scalar;
        }
    }
    return cpy;
}

template <typename K, size_t _r, size_t _c, typename K1, size_t _r1, size_t _c1>
Matrix<K, _r, _c> operator*(const Matrix<K, _r, _c>& first, const Matrix<K1, _r1, _c1> second) {
    Matrix cpy(first);
    return cpy;
}

template <typename K, size_t _r, size_t _c>
Matrix<K, _r, _c> operator+(const int scalar, const Matrix<K, _r, _c>& other) {
    Matrix cpy(other);
    for (int i = 0; i < _r; i++) {
        for (int j = 0; j < _c; j++) {
            cpy.at(i, j) = cpy.at(i, j) + scalar;
        }
    }
    return cpy;
}

template <typename K, size_t _r, size_t _c>
Matrix<K, _r, _c> operator-(const int scalar, const Matrix<K, _r, _c>& other) {
    Matrix cpy(other);
    for (int i = 0; i < _r; i++) {
        for (int j = 0; j < _c; j++) {
            cpy.at(i, j) = cpy.at(i, j) - scalar;
        }
    }
    return cpy;
}
#endif  /// MATRIX_SRC_MATRIX_H.

int main() {
    return 0;
}
