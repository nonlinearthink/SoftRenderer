#pragma once

#include "SoftRenderer/matrix.h"
#include "SoftRenderer/vec.h"

namespace SoftRenderer {
class Transform {
public:
    Transform() = default;
    explicit Transform(Matrix4& matrix)
        : matrix_{matrix}, inverse_matrix_{matrix.Invert()} {}

    static Transform Translate(const Vector3f& position);
    static Transform RotateX(float radian);
    static Transform RotateY(float radian);
    static Transform RotateZ(float radian);
    static Transform Rotate(const Vector3f& rotation);
    static Transform Scale(const Vector3f& scaling);
    // camera view transform
    static Transform LookAt(const Vector3f& eye, const Vector3f& gaze,
                            const Vector3f& up);
    // orthographic projection: (l,b,n)->(-1,-1,1), (r,t,f)->(1,1,-1)
    static Transform Orthographic(float left, float right, float bottom,
                                  float top, float far, float near);
    // perspective projection
    static Transform Perspective(float left, float right, float bottom,
                                 float top, float far, float near);
    // Transform a vector from the [-1,1]^3 cube coordinate space to
    // [0,width]×[0,height] screen space.
    static Transform Viewport(int width, int height);

    inline Matrix4 matrix();
    inline Matrix4 inverse_matrix();

    Transform operator*(const Transform& rhs) const;

private:
    Matrix4 matrix_{Matrix4::Identity()};
    Matrix4 inverse_matrix_{Matrix4::Identity()};
};

inline Matrix4 Transform::matrix() { return matrix_; }

inline Matrix4 Transform::inverse_matrix() { return inverse_matrix_; }
}  // namespace SoftRenderer
