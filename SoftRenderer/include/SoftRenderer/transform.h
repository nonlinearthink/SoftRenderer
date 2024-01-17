#pragma once

#include "SoftRenderer/matrix.h"
#include "SoftRenderer/vec.h"

namespace SoftRenderer {
class Transform {
public:
    static Matrix4 Translate(const Vector3f& position);
    static Matrix4 RotateX(float radian);
    static Matrix4 RotateY(float radian);
    static Matrix4 RotateZ(float radian);
    static Matrix4 Rotate(const Vector3f& rotation);
    static Matrix4 Scale(const Vector3f& scaling);

    [[nodiscard]] inline Vector3f position() const;
    inline Transform& set_position(const Vector3f& position);
    [[nodiscard]] inline Vector3f rotation() const;
    inline Transform& set_rotation(const Vector3f& rotation);
    [[nodiscard]] inline Vector3f scaling() const;
    inline Transform& set_scaling(const Vector3f& scaling);
    inline Matrix4 matrix();
    inline Matrix4 inverse_matrix();

private:
    Vector3f position_{0, 0, 0};
    Vector3f rotation_{0, 0, 0};
    Vector3f scaling_{1, 1, 1};
    bool is_dirty_{false};
    Matrix4 matrix_{Matrix4::Identity()};
    Matrix4 inverse_matrix_{Matrix4::Identity()};

    void UpdateTransformMatrix();
};

inline Vector3f Transform::position() const { return position_; };

inline Transform& Transform::set_position(const Vector3f& position) {
    if (position_ != position) {
        position_.CopyFrom(position);
        is_dirty_ = true;
    }
    return *this;
}

inline Vector3f Transform::rotation() const { return rotation_; };

inline Transform& Transform::set_rotation(const Vector3f& rotation) {
    if (rotation_ != rotation) {
        rotation_.CopyFrom(rotation);
        is_dirty_ = true;
    }
    return *this;
}

inline Vector3f Transform::scaling() const { return scaling_; };

inline Transform& Transform::set_scaling(const Vector3f& scaling) {
    if (scaling_ != scaling) {
        scaling_.CopyFrom(scaling);
        is_dirty_ = true;
    }
    return *this;
}

inline Matrix4 Transform::matrix() {
    if (is_dirty_) {
        UpdateTransformMatrix();
    }
    return matrix_;
}

inline Matrix4 Transform::inverse_matrix() {
    if (is_dirty_) {
        UpdateTransformMatrix();
    }
    return inverse_matrix_;
}
}  // namespace SoftRenderer
