#pragma once

#include <istream>

namespace SoftRenderer {
template <typename T>
class Vector2 {
public:
    T x, y;

    Vector2<T>() : x{0}, y{0} {}
    Vector2<T>(T x, T y) : x{x}, y{y} {}
    Vector2<T>(const Vector2<T>& v) : x{v.x}, y{v.y} {}

    inline T operator[](size_t n) const;
    inline Vector2<T> operator+(const Vector2<T>& rhs) const;
    inline Vector2<T> operator-(const Vector2<T>& rhs) const;
    inline Vector2<T> operator*(const Vector2<T>& rhs) const;
    inline Vector2<T> operator*(T k) const;
    inline bool operator==(const Vector2<T>& rhs) const;
    inline bool operator!=(const Vector2<T>& rhs) const;

    inline void CopyFrom(const Vector2<T>& v);
};

#pragma region Vector2 Template Implementation

template <typename T>
inline T Vector2<T>::operator[](size_t n) const {
    if (n == 1) {
        return y;
    } else {
        return x;
    }
}

template <typename T>
inline Vector2<T> Vector2<T>::operator+(const Vector2<T>& rhs) const {
    return {x + rhs.x, y + rhs.y};
};

template <typename T>
inline Vector2<T> Vector2<T>::operator-(const Vector2<T>& rhs) const {
    return {x - rhs.x, y - rhs.y};
};

template <typename T>
inline Vector2<T> Vector2<T>::operator*(const Vector2<T>& rhs) const {
    return {x * rhs.x, y * rhs.y};
};

template <typename T>
inline Vector2<T> Vector2<T>::operator*(T k) const {
    return {x * k, y * k};
};

template <typename T>
inline bool Vector2<T>::operator==(const Vector2<T>& rhs) const {
    return x == rhs.x && y == rhs.y;
}

template <typename T>
inline bool Vector2<T>::operator!=(const Vector2<T>& rhs) const {
    return x != rhs.x || y != rhs.y;
}

template <typename T>
inline void Vector2<T>::CopyFrom(const Vector2<T>& v) {
    x = v.x;
    y = v.y;
}

#pragma endregion Vector2 Template Implementation

template <typename T>
class Vector3 {
public:
    T x, y, z;

    Vector3<T>() : x{0}, y{0}, z{0} {}
    Vector3<T>(T x, T y, T z) : x{x}, y{y}, z{z} {}
    Vector3<T>(const Vector3<T>& v) : x{v.x}, y{v.y}, z{v.z} {}

    T operator[](size_t n) const;
    inline Vector3<T> operator+(const Vector3<T>& rhs) const;
    inline Vector3<T> operator-(const Vector3<T>& rhs) const;
    inline Vector3<T> operator*(const Vector3<T>& rhs) const;
    inline Vector3<T> operator*(T k) const;
    constexpr bool operator==(const Vector3<T>& rhs) const;
    constexpr bool operator!=(const Vector3<T>& rhs) const;

    [[nodiscard]] constexpr float Length() const;
    [[nodiscard]] constexpr float LengthSquare() const;
    constexpr T Dot(const Vector3<T>& rhs) const;
    Vector3<T> Cross(const Vector3<T>& rhs) const;
    Vector3<T> Normalize() const;

    inline void CopyFrom(const Vector3<T>& v);
};

#pragma region Vector3 Template Implementation

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
    return {x + rhs.x, y + rhs.y, z + rhs.z};
};

template <typename T>
inline Vector3<T> Vector3<T>::operator-(const Vector3<T>& rhs) const {
    return {x - rhs.x, y - rhs.y, z - rhs.z};
};

template <typename T>
inline Vector3<T> Vector3<T>::operator*(const Vector3<T>& rhs) const {
    return {x * rhs.x, y * rhs.y, z * rhs.z};
};

template <typename T>
inline Vector3<T> Vector3<T>::operator*(const T k) const {
    return {x * k, y * k, z * k};
};

template <typename T>
constexpr bool Vector3<T>::operator==(const Vector3<T>& rhs) const {
    return x == rhs.x && y == rhs.y && z == rhs.z;
}

template <typename T>
constexpr bool Vector3<T>::operator!=(const Vector3<T>& rhs) const {
    return x != rhs.x || y != rhs.y || z != rhs.z;
}

template <typename T>
constexpr float Vector3<T>::LengthSquare() const {
    return x * x + y * y + z * z;
}

template <typename T>
constexpr float Vector3<T>::Length() const {
    return std::sqrt(LengthSquare());
}

template <typename T>
constexpr T Vector3<T>::Dot(const Vector3<T>& rhs) const {
    return x * rhs.x + y * rhs.y + z * rhs.z;
}

template <typename T>
Vector3<T> Vector3<T>::Cross(const Vector3<T>& rhs) const {
    return {y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z,
            x * rhs.y - y * rhs.x};
}

template <typename T>
Vector3<T> Vector3<T>::Normalize() const {
    float len = Length();
    if (len != 0) {
        return {x / len, y / len, z / len};
    } else {
        return {*this};
    }
}

template <typename T>
inline void Vector3<T>::CopyFrom(const Vector3<T>& v) {
    x = v.x;
    y = v.y;
    z = v.z;
}

#pragma endregion Vector3 Template Implementation

using Vector2f = Vector2<float>;
using Vector2i = Vector2<int>;
using Vector3f = Vector3<float>;
using Vector3i = Vector3<int>;
}  // namespace SoftRenderer
