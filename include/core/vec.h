template <typename T, size_t N>
class BaseVectorN {
   public:
    BaseVectorN<T, N>();
    ~BaseVectorN<T, N>();

    T &operator[](size_t i) const;
    BaseVectorN<T, N> &operator-() const;
    BaseVectorN<T, N> operator+(const T &rhs) const;
    BaseVectorN<T, N> operator-(const T &rhs) const;
    BaseVectorN<T, N> operator*(const T &rhs) const;
    BaseVectorN<T, N> operator/(const T &rhs) const;
    BaseVectorN<T, N> operator+(const BaseVectorN<T, N> &rhs) const;
    BaseVectorN<T, N> operator-(const BaseVectorN<T, N> &rhs) const;
    BaseVectorN<T, N> operator*(const BaseVectorN<T, N> &rhs) const;
    BaseVectorN<T, N> operator/(const BaseVectorN<T, N> &rhs) const;
    BaseVectorN<T, N> &operator+=(const BaseVectorN<T, N> &rhs);
    BaseVectorN<T, N> &operator-=(const BaseVectorN<T, N> &rhs);
    BaseVectorN<T, N> &operator*=(const BaseVectorN<T, N> &rhs);
    BaseVectorN<T, N> &operator/=(const BaseVectorN<T, N> &rhs);

   protected:
    T _v[N]{};
};

template <typename T>
class Vector2 : protected BaseVectorN<T, 2> {
   public:
    Vector2<T>() : BaseVectorN<T, 2>(){};
    Vector2<T>(T x, T y);

    T &x() const;
    T &y() const;
    void setX(T x);
    void setY(T y);
};

template <typename T>
class Vector3 : protected BaseVectorN<T, 3> {
   public:
    Vector3<T>() : BaseVectorN<T, 3>(){};
    Vector3<T>(T x, T y, T z);

    T &x() const;
    T &y() const;
    T &z() const;
    void setX(T x);
    void setY(T y);
    void setZ(T z);
};

template <typename T>
class Vector4 : protected BaseVectorN<T, 4> {
   public:
    Vector4<T>() : BaseVectorN<T, 4>(){};
    Vector4<T>(T x, T y, T z, T w);

    T &x() const;
    T &y() const;
    T &z() const;
    T &w() const;
    void setX(T x);
    void setY(T y);
    void setZ(T z);
    void setW(T w);
};

using Vector2f = Vector2<float>;
using Vector2i = Vector2<int>;
using Vector3f = Vector3<float>;
using Vector3i = Vector3<int>;
using Vector4f = Vector4<float>;
using Vector4i = Vector4<int>;
