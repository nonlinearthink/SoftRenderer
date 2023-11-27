#pragma once

 #include <vcruntime.h>

template <size_t N>
class Matrix {
   public:
    Matrix<N>();
    ~Matrix<N>();

    Matrix<N> operator+(const Matrix<N>& rhs) const;
    Matrix<N> operator-(const Matrix<N>& rhs) const;
    Matrix<N> operator*(const Matrix<N>& rhs) const;
    Matrix<N> operator*(float k) const;
    Matrix<N> operator/(float k) const;
    bool operator==(const Matrix<N>& rhs) const;

   private:
    float _m[4][4]{};
};

using Matrix4 = Matrix<4>;
