#include "SoftRenderer/transform.h"

#include "SoftRenderer/common.h"
#include "SoftRenderer/matrix.h"
#include "SoftRenderer/vec.h"

using namespace SoftRenderer;

Matrix4 Transform::Translate(const Vector3f &position) {
    Matrix4 transform{Matrix4::Identity()};
    transform.m[0][3] = position.x;
    transform.m[1][3] = position.y;
    transform.m[2][3] = position.z;
    return transform;
}

Matrix4 Transform::RotateX(float radian) {
    float cos_value{cos(radian)};
    float sin_value{sin(radian)};

    Matrix4 transform{Matrix4::Identity()};
    transform.m[1][1] = cos_value;
    transform.m[1][2] = -sin_value;
    transform.m[2][1] = sin_value;
    transform.m[2][2] = cos_value;

    return transform;
}

Matrix4 Transform::RotateY(float radian) {
    float cos_value{cos(radian)};
    float sin_value{sin(radian)};

    Matrix4 transform{Matrix4::Identity()};
    transform.m[0][0] = cos_value;
    transform.m[0][2] = sin_value;
    transform.m[2][0] = -sin_value;
    transform.m[2][2] = cos_value;

    return transform;
}

Matrix4 Transform::RotateZ(float radian) {
    float cos_value{cos(radian)};
    float sin_value{sin(radian)};

    Matrix4 transform{Matrix4::Identity()};
    transform.m[0][0] = cos_value;
    transform.m[0][1] = -sin_value;
    transform.m[1][0] = sin_value;
    transform.m[1][1] = cos_value;

    return transform;
}

Matrix4 Transform::Rotate(const Vector3f &rotation) {
    return RotateX(rotation.x) * RotateY(rotation.y) * RotateZ(rotation.z);
}

Matrix4 Transform::Scale(const Vector3f &scaling) {
    Matrix4 transform{Matrix4::Identity()};
    transform.m[0][0] = scaling.x;
    transform.m[1][1] = scaling.y;
    transform.m[2][2] = scaling.z;
    return transform;
}

void Transform::UpdateTransformMatrix() {
    if (!is_dirty_) {
        return;
    }
    matrix_ = Transform::Scale(scaling_) * Transform::Rotate(rotation_) *
              Transform::Translate(position_);
    auto inverse_matrix_optional = matrix_.Invert();
    if (inverse_matrix_optional.has_value()) {
        inverse_matrix_ = inverse_matrix_optional.value();
    } else {
        inverse_matrix_ = Matrix4::Identity();
    }
}
