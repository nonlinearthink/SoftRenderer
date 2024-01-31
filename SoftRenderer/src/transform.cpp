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
    Vector3f w = gaze.Normalize() * -1;
    Vector3f u = up.Cross(w).Normalize();
    Vector3f v = w.Cross(u).Normalize();
    Matrix4 translate{1, 0, 0, -eye.x, 0, 1, 0, -eye.y,
                      0, 0, 1, -eye.z, 0, 0, 0, 1};
    Matrix4 rotation{u.x, u.y, u.z, 0, v.x, v.y, v.z, 0,
                     w.x, w.y, w.z, 0, 0,   0,   0,   1};
    Matrix4 matrix{rotation * translate};
    return Transform{matrix};
}

Transform Transform::Orthographic(float left, float right, float bottom,
                                  float top, float far, float near) {
    Matrix4 matrix{2 / (right - left),
                   0,
                   0,
                   -(right + left) / (right - left),
                   0,
                   2 / (top - bottom),
                   0,
                   -(top + bottom) / (top - bottom),
                   0,
                   0,
                   2 / (near - far),
                   -(near + far) / (near - far),
                   0,
                   0,
                   0,
                   1};
    return Transform{matrix};
}

Transform Transform::Perspective(float left, float right, float bottom,
                                 float top, float far, float near) {
    // M_per = M_orth * P, P is a transform matrix from perspective frustum to
    // orthographic cuboid.
    Matrix4 matrix{2 * near / (right - left),
                   0,
                   0,
                   (right + left) / (right - left),
                   0,
                   2 * near / (top - bottom),
                   0,
                   (top + bottom) / (top - bottom),
                   0,
                   0,
                   0,
                   (near + far) / (near - far),
                   2 * far * near / (far - near),
                   0,
                   0,
                   1,
                   0};
    return Transform{matrix};
}

Transform Transform::Viewport(int width, int height) {
    float half_width = static_cast<float>(width) / 2.f;
    float half_height = static_cast<float>(height) / 2.f;
    Matrix4 matrix{half_width,
                   0,
                   half_width - 0.5f,
                   0,
                   0,
                   half_height,
                   half_height - 0.5f,
                   0,
                   0,
                   0,
                   1,
                   0,
                   0,
                   0,
                   0,
                   1};
    return Transform{matrix};
}

Transform Transform::operator*(const Transform &rhs) const {
    Matrix4 matrix{matrix_ * rhs.matrix_};
    return Transform{matrix};
}

Vector3f Transform::TransformVector(const Vector3f &vec) const {
    float x = matrix_.m[0][0] * vec.x + matrix_.m[0][1] * vec.y +
              matrix_.m[0][2] * vec.z + matrix_.m[0][3];
    float y = matrix_.m[1][0] * vec.x + matrix_.m[1][1] * vec.y +
              matrix_.m[1][2] * vec.z + matrix_.m[1][3];
    float z = matrix_.m[2][0] * vec.x + matrix_.m[2][1] * vec.y +
              matrix_.m[2][2] * vec.z + matrix_.m[2][3];
    float w = matrix_.m[3][0] * vec.x + matrix_.m[3][1] * vec.y +
              matrix_.m[3][2] * vec.z + matrix_.m[3][3];
#ifdef _DEBUG
    assert(w != 0);
#endif
    return {x / w, y / w, z / w};
}
