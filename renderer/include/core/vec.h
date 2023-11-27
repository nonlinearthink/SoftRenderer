#pragma once

template <typename T>
class Vector2 {
   public:
    T x, y;

    Vector2<T>() : x(), y() {}
    Vector2<T>(T _x, T _y) : x(_x), y(_y) {}

    inline Vector2<T> operator+(const Vector2<T>& rhs) const;
    inline Vector2<T> operator-(const Vector2<T>& rhs) const;
    inline Vector2<T> operator*(const Vector2<T>& rhs) const;
};

template <typename T>
inline Vector2<T> Vector2<T>::operator+(const Vector2<T>& rhs) const {
    return Vector2(x + rhs.x, y + rhs.y);
};

template <typename T>
inline Vector2<T> Vector2<T>::operator-(const Vector2<T>& rhs) const {
    return Vector2(x - rhs.x, y - rhs.y);
};

template <typename T>
inline Vector2<T> Vector2<T>::operator*(const Vector2<T>& rhs) const {
    return Vector2(x * rhs.x, y * rhs.y);
};

template <typename T>
class Vector3 {
   public:
    T x, y, z;

    Vector3<T>() : x(), y(), z() {}
    Vector3<T>(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}

    inline Vector3<T> operator+(const Vector3<T>& rhs) const;
    inline Vector3<T> operator-(const Vector3<T>& rhs) const;
    inline Vector3<T> operator*(const Vector3<T>& rhs) const;
};

template <typename T>
inline Vector3<T> Vector3<T>::operator+(const Vector3<T>& rhs) const {
    return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
};

template <typename T>
inline Vector3<T> Vector3<T>::operator-(const Vector3<T>& rhs) const {
    return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
};

template <typename T>
inline Vector3<T> Vector3<T>::operator*(const Vector3<T>& rhs) const {
    return Vector3(x * rhs.x, y * rhs.y, z * rhs.z);
};

using Vector2f = Vector2<float>;
using Vector2i = Vector2<int>;
using Vector3f = Vector3<float>;
using Vector3i = Vector3<int>;
