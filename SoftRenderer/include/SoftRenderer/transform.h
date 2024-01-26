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
    static Transform LookAt(const Vector3f& eye, const Vector3f& gaze,
                            const Vector3f& up);
    static Transform Orthographic(float near_z, float far_z);
    static Transform Perspective(float fov, float near_z, float far_z);

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
