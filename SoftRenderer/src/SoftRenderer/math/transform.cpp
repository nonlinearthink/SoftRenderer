#include "SoftRenderer/math/transform.h"

#include "SoftRenderer/math/common.h"
#include "SoftRenderer/math/matrix.hpp"

using namespace SoftRenderer;

Matrix4 Transform::GetTransformMatrix() const { return m_; }

Transform& Transform::Translate(const Vector3f position) {
    position_ = position;

    Matrix4 transform = Matrix4::Identity();
    transform.m[0][3] = position_.x;
    transform.m[1][3] = position_.y;
    transform.m[2][3] = position_.z;

    m_ = m_ * transform;

    return *this;
}

Transform& Transform::RotateX(const float angle) {
    float radian = DegreeToRadian(angle);
    float cos_value = cos(radian);
    float sin_value = sin(radian);

    rotation_.x = radian;

    Matrix4 transform = Matrix4::Identity();
    transform.m[1][1] = cos_value;
    transform.m[1][2] = -sin_value;
    transform.m[2][1] = sin_value;
    transform.m[2][2] = cos_value;

    m_ = m_ * transform;

    return *this;
}

Transform& Transform::RotateY(const float angle) {
    float radian = DegreeToRadian(angle);
    float cos_value = cos(radian);
    float sin_value = sin(radian);

    rotation_.y = radian;

    Matrix4 transform = Matrix4::Identity();
    transform.m[0][0] = cos_value;
    transform.m[0][2] = sin_value;
    transform.m[2][0] = -sin_value;
    transform.m[2][2] = cos_value;

    m_ = m_ * transform;

    return *this;
}

Transform& Transform::RotateZ(const float angle) {
    float radian = DegreeToRadian(angle);
    float cos_value = cos(radian);
    float sin_value = sin(radian);

    rotation_.z = radian;

    Matrix4 transform = Matrix4::Identity();
    transform.m[0][0] = cos_value;
    transform.m[0][1] = -sin_value;
    transform.m[1][0] = sin_value;
    transform.m[1][1] = cos_value;

    m_ = m_ * transform;

    return *this;
}

Transform& Transform::Rotation(const Vector3f rotation) {
    rotation_ = rotation;
    RotateX(rotation.x);
    RotateY(rotation.y);
    RotateZ(rotation.z);
    return *this;
}

Transform& Transform::Scale(const Vector3f scaling) {
    scaling_ = scaling;

    Matrix4 transform;
    transform.m[0][0] = scaling_.x;
    transform.m[1][1] = scaling_.y;
    transform.m[2][2] = scaling_.z;
    transform.m[3][3] = 1;

    m_ = m_ * transform;

    return *this;
}
