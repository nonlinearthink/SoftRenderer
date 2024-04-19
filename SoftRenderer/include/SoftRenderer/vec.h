#pragma once

#include <istream>
#include <stdexcept>

#include "SoftRenderer/common.h"

namespace SoftRenderer {
template <typename T>
class Vector2 {
public:
    T x, y;

    Vector2<T>() : x{0}, y{0} {}
    Vector2<T>(T x, T y) : x{x}, y{y} {}

    T operator[](size_t n) const {
        if (n == 0) {
            return x;
        } else if (n == 1) {
            return y;
        } else {
            throw std::runtime_error("access out of range");
        }
    }
    constexpr Vector2<T> operator+(const Vector2<T>& rhs) const {
        return {x + rhs.x, y + rhs.y};
    };
    constexpr Vector2<T> operator-(const Vector2<T>& rhs) const {
        return {x - rhs.x, y - rhs.y};
    };
    constexpr Vector2<T> operator*(const Vector2<T>& rhs) const {
        return {x * rhs.x, y * rhs.y};
    };
    constexpr Vector2<T> operator*(T k) const { return {x * k, y * k}; };
    inline bool operator==(const Vector2<T>& rhs) const {
        return x == rhs.x && y == rhs.y;
    }
    inline bool operator!=(const Vector2<T>& rhs) const {
        return x != rhs.x || y != rhs.y;
    }
    friend std::ostream& operator<<(std::ostream& os, const Vector2<T>& v) {
        return os << "Vector2<" << typeid(T).name() << ">(" << v.x << ", "
                  << v.y << ")";
    }

    constexpr void CopyFrom(const Vector2<T>& v) noexcept {
        x = v.x;
        y = v.y;
    }
};

template <>
inline bool Vector2<float>::operator==(const Vector2<float>& rhs) const {
    using namespace MathUtils;
    return Equals(x, rhs.x) && Equals(y, rhs.y);
}

template <>
inline bool Vector2<float>::operator!=(const Vector2<float>& rhs) const {
    using namespace MathUtils;
    return Equals(x, rhs.x) || Equals(y, rhs.y);
}

template <typename T>
class Vector3 {
public:
    T x, y, z, w;

    Vector3<T>() : x{0}, y{0}, z{0}, w{1} {}
    Vector3<T>(T x, T y, T z) : x{x}, y{y}, z{z}, w{1} {}

    T operator[](size_t n) const {
        if (n == 0) {
            return x;
        } else if (n == 1) {
            return y;
        } else if (n == 2) {
            return z;
        } else {
            throw std::runtime_error("access out of range");
        }
    }
    constexpr Vector3<T> operator+(const Vector3<T>& rhs) const {
        return {x + rhs.x, y + rhs.y, z + rhs.z};
    };
    constexpr Vector3<T> operator-(const Vector3<T>& rhs) const {
        return {x - rhs.x, y - rhs.y, z - rhs.z};
    };
    constexpr Vector3<T> operator*(const Vector3<T>& rhs) const {
        return {x * rhs.x, y * rhs.y, z * rhs.z};
    };
    constexpr Vector3<T> operator*(T k) const { return {x * k, y * k, z * k}; };
    inline bool operator==(const Vector3<T>& rhs) const {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }
    inline bool operator!=(const Vector3<T>& rhs) const {
        return x != rhs.x || y != rhs.y || z != rhs.z;
    }
    friend constexpr std::ostream& operator<<(std::ostream& os,
                                              const Vector3<T>& v) {
        return os << "Vector3<" << typeid(T).name() << ">(" << v.x << ", "
                  << v.y << ", " << v.z << ")";
    }

    constexpr void CopyFrom(const Vector3<T>& v) noexcept {
        x = v.x;
        y = v.y;
        z = v.z;
    }
    [[nodiscard]] constexpr float Length() const {
        return std::sqrt(LengthSquare());
    }
    [[nodiscard]] constexpr float LengthSquare() const noexcept {
        return x * x + y * y + z * z;
    }
    [[nodiscard]] constexpr T Dot(const Vector3<T>& rhs) const noexcept {
        return x * rhs.x + y * rhs.y + z * rhs.z;
    }
    [[nodiscard]] constexpr Vector3<T> Cross(const Vector3<T>& rhs) const {
        return {y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z,
                x * rhs.y - y * rhs.x};
    }
    [[nodiscard]] constexpr Vector3<T> Normalize() const {
        float len = Length();
        if (len != 0) {
            return {x / len, y / len, z / len};
        } else {
            return {*this};
        }
    }
};

template <>
inline bool Vector3<float>::operator==(const Vector3<float>& rhs) const {
    using namespace MathUtils;
    return Equals(x, rhs.x) && Equals(y, rhs.y) && Equals(z, rhs.z);
}

template <>
inline bool Vector3<float>::operator!=(const Vector3<float>& rhs) const {
    using namespace MathUtils;
    return !Equals(x, rhs.x) || !Equals(y, rhs.y) || !Equals(z, rhs.z);
}

using Vector2f = Vector2<float>;
using Vector2i = Vector2<int>;
using Vector3f = Vector3<float>;
using Vector3i = Vector3<int>;
}  // namespace SoftRenderer
