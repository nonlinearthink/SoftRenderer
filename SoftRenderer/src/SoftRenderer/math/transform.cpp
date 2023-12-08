#include "SoftRenderer/math/transform.h"

#include "SoftRenderer/math/common.h"
#include "SoftRenderer/math/matrix.h"

using namespace SoftRenderer;

Transform& Transform::Translate(const Vector3f _position) {
    position = _position;

    Matrix transform = Matrix::Identity();
    transform.m[0][3] = position.x;
    transform.m[1][3] = position.y;
    transform.m[2][3] = position.z;

    m = m * transform;

    return *this;
}

Transform& Transform::RotateX(const float angle) {
    float radian = DegreeToRadian(angle);
    float cos_value = cos(radian);
    float sin_value = sin(radian);

    rotation.x = radian;

    Matrix transform = Matrix::Identity();
    transform.m[1][1] = cos_value;
    transform.m[1][2] = -sin_value;
    transform.m[2][1] = sin_value;
    transform.m[2][2] = cos_value;

    m = m * transform;

    return *this;
}

Transform& Transform::RotateY(const float angle) {
    float radian = DegreeToRadian(angle);
    float cos_value = cos(radian);
    float sin_value = sin(radian);

    rotation.y = radian;

    Matrix transform = Matrix::Identity();
    transform.m[0][0] = cos_value;
    transform.m[0][2] = sin_value;
    transform.m[2][0] = -sin_value;
    transform.m[2][2] = cos_value;

    m = m * transform;

    return *this;
}

Transform& Transform::RotateZ(const float angle) {
    float radian = DegreeToRadian(angle);
    float cos_value = cos(radian);
    float sin_value = sin(radian);

    rotation.z = radian;

    Matrix transform = Matrix::Identity();
    transform.m[0][0] = cos_value;
    transform.m[0][1] = -sin_value;
    transform.m[1][0] = sin_value;
    transform.m[1][1] = cos_value;

    m = m * transform;

    return *this;
}

Transform& Transform::Rotation(const Vector3f _rotation) {
    rotation = _rotation;
    RotateX(_rotation.x);
    RotateY(_rotation.y);
    RotateZ(_rotation.z);
    return *this;
}

Transform& Transform::Scale(const Vector3f _scaling) {
    scaling = _scaling;

    Matrix transform;
    transform.m[0][0] = scaling.x;
    transform.m[1][1] = scaling.y;
    transform.m[2][2] = scaling.z;
    transform.m[3][3] = 1;

    m = m * transform;

    return *this;
}
