#include "core/vec.h"

// #include "core/vec.h"

// template <typename T, size_t N>
// BaseVectorN<T, N>::BaseVectorN() {
//     _v = new T[N];
// }

// template <typename T, size_t N>
// BaseVectorN<T, N>::~BaseVectorN() {
//     delete[] _v;
// }

// template <typename T, size_t N>
// T &BaseVectorN<T, N>::operator[](size_t i) const {
//     return _v[i];
// };

// template <typename T, size_t N>
// BaseVectorN<T, N> &BaseVectorN<T, N>::operator-() const {
//     BaseVectorN<T, N> &newV{};
//     for (size_t i = 0; i < N; i++) {
//         newV._v[i] = -_v[i];
//     }
//     return newV;
// };

// template <typename T, size_t N>
// BaseVectorN<T, N> BaseVectorN<T, N>::operator+(const T &rhs) const {
//     BaseVectorN<T, N> &newV{};
//     for (size_t i = 0; i < N; i++) {
//         newV._v[i] = _v[i] + rhs;
//     }
//     return newV;
// };

// template <typename T, size_t N>
// BaseVectorN<T, N> BaseVectorN<T, N>::operator-(const T &rhs) const {
//     BaseVectorN<T, N> &newV{};
//     for (size_t i = 0; i < N; i++) {
//         newV._v[i] = _v[i] - rhs;
//     }
//     return newV;
// };

// template <typename T, size_t N>
// BaseVectorN<T, N> BaseVectorN<T, N>::operator*(const T &rhs) const {
//     BaseVectorN<T, N> &newV{};
//     for (size_t i = 0; i < N; i++) {
//         newV._v[i] = _v[i] * rhs;
//     }
//     return newV;
// };

// template <typename T, size_t N>
// BaseVectorN<T, N> BaseVectorN<T, N>::operator/(const T &rhs) const {
//     BaseVectorN<T, N> &newV{};
//     for (size_t i = 0; i < N; i++) {
//         newV._v[i] = _v[i] / rhs;
//     }
//     return newV;
// };

// template <typename T, size_t N>
// BaseVectorN<T, N> BaseVectorN<T, N>::operator+(
//     const BaseVectorN<T, N> &rhs) const {
//     BaseVectorN<T, N> &newV{};
//     for (size_t i = 0; i < N; i++) {
//         newV._v[i] = _v[i] + rhs._v[i];
//     }
//     return newV;
// };

// template <typename T, size_t N>
// BaseVectorN<T, N> BaseVectorN<T, N>::operator-(
//     const BaseVectorN<T, N> &rhs) const {
//     BaseVectorN<T, N> &newV{};
//     for (size_t i = 0; i < N; i++) {
//         newV._v[i] = _v[i] - rhs._v[i];
//     }
//     return newV;
// };

// template <typename T, size_t N>
// BaseVectorN<T, N> BaseVectorN<T, N>::operator*(
//     const BaseVectorN<T, N> &rhs) const {
//     BaseVectorN<T, N> &newV{};
//     for (size_t i = 0; i < N; i++) {
//         newV._v[i] = _v[i] * rhs._v[i];
//     }
//     return newV;
// };

// template <typename T, size_t N>
// BaseVectorN<T, N> BaseVectorN<T, N>::operator/(
//     const BaseVectorN<T, N> &rhs) const {
//     BaseVectorN<T, N> &newV{};
//     for (size_t i = 0; i < N; i++) {
//         newV._v[i] = _v[i] / rhs._v[i];
//     }
//     return newV;
// };

// template <typename T, size_t N>
// BaseVectorN<T, N> &BaseVectorN<T, N>::operator+=(const BaseVectorN<T, N> &rhs) {
//     for (size_t i = 0; i < N; i++) {
//         _v[i] += rhs._v[i];
//     }
//     return this;
// };

// template <typename T, size_t N>
// BaseVectorN<T, N> &BaseVectorN<T, N>::operator-=(const BaseVectorN<T, N> &rhs) {
//     for (size_t i = 0; i < N; i++) {
//         _v[i] -= rhs._v[i];
//     }
//     return this;
// };

// template <typename T, size_t N>
// BaseVectorN<T, N> &BaseVectorN<T, N>::operator*=(const BaseVectorN<T, N> &rhs) {
//     for (size_t i = 0; i < N; i++) {
//         _v[i] *= rhs._v[i];
//     }
//     return this;
// };

// template <typename T, size_t N>
// BaseVectorN<T, N> &BaseVectorN<T, N>::operator/=(const BaseVectorN<T, N> &rhs) {
//     for (size_t i = 0; i < N; i++) {
//         _v[i] /= rhs._v[i];
//     }
//     return this;
// };

// template <typename T>
// Vector2<T>::Vector2(T x, T y) : BaseVectorN<T, 2>() {
//     this->_v[0] = x;
//     this->_v[1] = y;
// }

// template <typename T>
// T &Vector2<T>::x() const {
//     return this->_v[0];
// }

// template <typename T>
// T &Vector2<T>::y() const {
//     return this->_v[1];
// }

// template <typename T>
// void Vector2<T>::setX(T x) {
//     this->_v[0] = x;
// }

// template <typename T>
// void Vector2<T>::setY(T y) {
//     this->_v[1] = y;
// }

// template <typename T>
// Vector3<T>::Vector3(T x, T y, T z) : BaseVectorN<T, 3>() {
//     this->_v[0] = x;
//     this->_v[1] = y;
//     this->_v[2] = z;
// }

// template <typename T>
// T &Vector3<T>::x() const {
//     return this->_v[0];
// }

// template <typename T>
// T &Vector3<T>::y() const {
//     return this->_v[1];
// }

// template <typename T>
// T &Vector3<T>::z() const {
//     return this->_v[2];
// }

// template <typename T>
// void Vector3<T>::setX(T x) {
//     this->_v[0] = x;
// }

// template <typename T>
// void Vector3<T>::setY(T y) {
//     this->_v[1] = y;
// }

// template <typename T>
// void Vector3<T>::setZ(T z) {
//     this->_v[2] = z;
// }

// template <typename T>
// Vector4<T>::Vector4(T x, T y, T z, T w) : BaseVectorN<T, 4>() {
//     this->_v[0] = x;
//     this->_v[1] = y;
//     this->_v[2] = z;
//     this->_v[3] = w;
// }

// template <typename T>
// T &Vector4<T>::x() const {
//     return this->_v[0];
// }

// template <typename T>
// T &Vector4<T>::y() const {
//     return this->_v[1];
// }

// template <typename T>
// T &Vector4<T>::z() const {
//     return this->_v[2];
// }

// template <typename T>
// T &Vector4<T>::w() const {
//     return this->_v[3];
// }

// template <typename T>
// void Vector4<T>::setX(T x) {
//     this->_v[0] = x;
// }

// template <typename T>
// void Vector4<T>::setY(T y) {
//     this->_v[1] = y;
// }

// template <typename T>
// void Vector4<T>::setZ(T z) {
//     this->_v[2] = z;
// }

// template <typename T>
// void Vector4<T>::setW(T w) {
//     this->_v[3] = w;
// }
