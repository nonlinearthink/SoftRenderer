#include "SoftRenderer/transform.h"

#include "SoftRenderer/common.h"
#include "SoftRenderer/matrix.h"
#include "SoftRenderer/vec.h"

using namespace SoftRenderer;

Transform Transform::Translate(const Vector3f &position) {
    Matrix4 matrix{1, 0, 0, position.x, 0, 1, 0, position.y,
                   0, 0, 1, position.z, 0, 0, 0, 1};
    return Transform{matrix};
}

Transform Transform::RotateX(float radian) {
    float cos_value{cos(radian)};
    float sin_value{sin(radian)};

    Matrix4 matrix{1, 0,         0,         0, 0, cos_value, -sin_value, 0,
                   0, sin_value, cos_value, 0, 0, 0,         0,          1};
    return Transform{matrix};
}

Transform Transform::RotateY(float radian) {
    float cos_value{cos(radian)};
    float sin_value{sin(radian)};

    Matrix4 matrix{cos_value,  0, sin_value, 0, 0, 1, 0, 0,
                   -sin_value, 0, cos_value, 0, 0, 0, 0, 1};
    return Transform{matrix};
}

Transform Transform::RotateZ(float radian) {
    float cos_value{cos(radian)};
    float sin_value{sin(radian)};

    Matrix4 matrix{cos_value, -sin_value, 0, 0, sin_value, cos_value, 0, 0,
                   0,         0,          1, 0, 0,         0,         0, 1};
    return Transform{matrix};
}

Transform Transform::Rotate(const Vector3f &rotation) {
    return RotateX(rotation.x) * RotateY(rotation.y) * RotateZ(rotation.z);
}

Transform Transform::Scale(const Vector3f &scaling) {
    Matrix4 matrix{scaling.x, 0, 0,         0, 0, scaling.y, 0, 0,
                   0,         0, scaling.z, 0, 0, 0,         0, 1};
    return Transform{matrix};
}

Transform Transform::LookAt(const Vector3f &eye, const Vector3f &gaze,
                            const Vector3f &up) {
    Vector3f u = up.Cross(gaze).Normalize();
    Vector3f v = u.Cross(gaze).Normalize();
    Vector3f w = u.Cross(v).Normalize();
    Matrix4 matrix{u.x, v.x, w.x, -eye.x, u.y, v.y, w.y, -eye.y,
                   u.z, v.z, w.z, -eye.z, 0,   0,   0,   1};
    return Transform{matrix};
}

Transform Transform::Orthographic(float near_z, float far_z) {
    return Scale(Vector3f{1, 1, far_z - near_z}) *
           Translate(Vector3f{0, 0, -near_z});
}

Transform Transform::Perspective(float fov, float near_z, float far_z) {
    Matrix4 matrix{1,
                   0,
                   0,
                   0,
                   0,
                   1,
                   0,
                   0,
                   0,
                   0,
                   far_z / (far_z - near_z),
                   -far_z * near_z / (far_z - near_z),
                   0,
                   0,
                   1,
                   0};
    return Transform{matrix};
}

Transform Transform::operator*(const Transform &rhs) const {
    Matrix4 matrix{matrix_ * rhs.matrix_};
    return Transform{matrix};
}
