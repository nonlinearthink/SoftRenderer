#pragma once

#include <cmath>
#include <cstddef>

namespace SoftRenderer {
template <typename T>
class Vector2 {
public:
    T x, y;

    Vector2<T>() : x(), y() {}
    Vector2<T>(T _x, T _y) : x(_x), y(_y) {}
    explicit Vector2<T>(const Vector2<T>& v) : x(v.x), y(v.y) {}
    ~Vector2<T>() = default;

    T operator[](size_t n) const;
    inline Vector2<T> operator+(const Vector2<T>& rhs) const;
    inline Vector2<T> operator-(const Vector2<T>& rhs) const;
    inline Vector2<T> operator*(const Vector2<T>& rhs) const;
    inline Vector2<T> operator*(const T k) const;
};

template <typename T>
T Vector2<T>::operator[](size_t n) const {
    if (n == 1) {
        return y;
    } else {
        return x;
    }
}

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
inline Vector2<T> Vector2<T>::operator*(const T k) const {
    return Vector2(x * k, y * k);
};

template <typename T>
class Vector3 {
public:
    T x, y, z;

    Vector3<T>() : x(), y(), z() {}
    Vector3<T>(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
    Vector3<T>(const Vector3<T>& v) : x(v.x), y(v.y), z(v.z) {}
    ~Vector3<T>() = default;

    T operator[](size_t n) const;
    inline Vector3<T> operator+(const Vector3<T>& rhs) const;
    inline Vector3<T> operator-(const Vector3<T>& rhs) const;
    inline Vector3<T> operator*(const Vector3<T>& rhs) const;
    inline Vector3<T> operator*(const T k) const;

    float Length() const;
    float LengthSquare() const;
    T Dot(const Vector3<T>& rhs) const;
    Vector3<T> Cross(const Vector3<T>& rhs) const;
    Vector3<T>& Normalize();
};

template <typename T>
T Vector3<T>::operator[](size_t n) const {
    if (n == 1) {
        return y;
    } else if (n == 2) {
        return z;
    } else {
        return x;
    }
}

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

template <typename T>
inline Vector3<T> Vector3<T>::operator*(const T k) const {
    return Vector3(x * k, y * k, z * k);
};

template <typename T>
float Vector3<T>::LengthSquare() const {
    return x * x + y * y + z * z;
}

template <typename T>
float Vector3<T>::Length() const {
    return std::sqrt(LengthSquare());
}

template <typename T>
T Vector3<T>::Dot(const Vector3<T>& rhs) const {
    return x * rhs.x + y * rhs.y + z * rhs.z;
}

template <typename T>
Vector3<T> Vector3<T>::Cross(const Vector3<T>& rhs) const {
    return Vector3<T>(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z,
                      x * rhs.y - y * rhs.x);
}

template <typename T>
Vector3<T>& Vector3<T>::Normalize() {
    float len = Length();
    if (len != 0) {
        x /= len;
        y /= len;
        z /= len;
    }
    return *this;
}

using Vector2f = Vector2<float>;
using Vector2i = Vector2<int>;
using Vector3f = Vector3<float>;
using Vector3i = Vector3<int>;
}  // namespace SoftRenderer
