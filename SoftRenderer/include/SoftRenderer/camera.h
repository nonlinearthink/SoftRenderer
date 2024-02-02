#pragma once

#include "SoftRenderer/camera.h"
#include "SoftRenderer/transform.h"
#include "SoftRenderer/vec.h"

namespace SoftRenderer {
enum class ProjectionMode { PERSPECTIVE, ORTHOGRAPHIC };

constexpr float DEFAULT_FOV = 30;
constexpr float DEFAULT_ASPECT = 16.f / 9.f;
constexpr float DEFAULT_NEAR_Z = -1;
constexpr float DEFAULT_FAR_Z = -1000;
constexpr ProjectionMode DEFAULT_PROJECTION_MODE = ProjectionMode::PERSPECTIVE;

// Camera Class
class Camera {
public:
    Camera(const Vector3f& position, const Vector3f& target, const Vector3f& up)
        : position_{position}, target_{target}, up_{up} {};

    inline void set_position(const Vector3f& position);
    inline void set_target(const Vector3f& target);
    inline void set_up(const Vector3f& up);
    inline void set_fov(float fov);
    inline void set_aspect(float aspect);
    inline void set_near_z(float near_z);
    inline void set_far_z(float far_z);
    inline void set_projection_mode(ProjectionMode projection_mode);

    // Updates per frame to compute the view matrix and projection
    // matrix of this camera.
    void Update();

private:
    Vector3f position_;
    Vector3f target_;
    Vector3f up_;

    float fov_{DEFAULT_FOV};
    float aspect_{DEFAULT_ASPECT};
    float near_z_{DEFAULT_FAR_Z};
    float far_z_{DEFAULT_FAR_Z};
    ProjectionMode projection_mode_{DEFAULT_PROJECTION_MODE};

    Transform view_transform_;
    bool is_view_transform_dirty_{false};
    Transform projection_transform_;
    bool is_projection_transform_dirty_{false};

    void ComputeViewTransform();
    void ComputeProjectionTransform();
};

#pragma region Camera Inline Implementation
inline void Camera::set_position(const Vector3f& position) {
    is_view_transform_dirty_ = true;
    position_.CopyFrom(position);
}

inline void Camera::set_target(const Vector3f& target) {
    is_view_transform_dirty_ = true;
    target_.CopyFrom(target);
}

inline void Camera::set_up(const Vector3f& up) {
    is_view_transform_dirty_ = true;
    up_.CopyFrom(up);
}

inline void Camera::set_fov(float fov) {
    is_projection_transform_dirty_ = true;
    fov_ = fov;
}

inline void Camera::set_aspect(float aspect) {
    is_projection_transform_dirty_ = true;
    aspect_ = aspect;
}

inline void Camera::set_near_z(float near_z) {
    is_projection_transform_dirty_ = true;
    near_z_ = near_z;
}

inline void Camera::set_far_z(float far_z) {
    is_projection_transform_dirty_ = true;
    far_z_ = far_z;
}

inline void Camera::set_projection_mode(ProjectionMode projection_mode) {
    is_projection_transform_dirty_ = true;
    projection_mode_ = projection_mode;
}
#pragma endregion Camera Inline Implementation

class CameraBuilder {
public:
    inline CameraBuilder& SetPosition(const Vector3f& position);
    inline CameraBuilder& SetTarget(const Vector3f& target);
    inline CameraBuilder& SetUp(const Vector3f& up);
    inline CameraBuilder& SetFov(float fov);
    inline CameraBuilder& SetAspect(float aspect);
    inline CameraBuilder& SetNearZ(float near_z);
    inline CameraBuilder& SetFarZ(float far_z);
    inline CameraBuilder& SetProjectionMode(ProjectionMode projection_mode);
    [[nodiscard]] std::unique_ptr<Camera> Build() const;

private:
    Vector3f position_;
    Vector3f target_;
    Vector3f up_;

    float fov_{DEFAULT_FOV};
    float aspect_{DEFAULT_ASPECT};
    float near_z_{DEFAULT_FAR_Z};
    float far_z_{DEFAULT_FAR_Z};
    ProjectionMode projection_mode_{DEFAULT_PROJECTION_MODE};
};

#pragma region CameraBuilder Inline Implementation
inline CameraBuilder& CameraBuilder::SetPosition(const Vector3f& position) {
    position_.CopyFrom(position);
    return *this;
}

inline CameraBuilder& CameraBuilder::SetTarget(const Vector3f& target) {
    target_.CopyFrom(target);
    return *this;
}

inline CameraBuilder& CameraBuilder::SetUp(const Vector3f& up) {
    up_.CopyFrom(up);
    return *this;
}

inline CameraBuilder& CameraBuilder::SetFov(float fov) {
    fov_ = fov;
    return *this;
}

inline CameraBuilder& CameraBuilder::SetAspect(float aspect) {
    aspect_ = aspect;
    return *this;
}

inline CameraBuilder& CameraBuilder::SetNearZ(float near_z) {
    near_z_ = near_z;
    return *this;
}

inline CameraBuilder& CameraBuilder::SetFarZ(float far_z) {
    far_z_ = far_z;
    return *this;
}

inline CameraBuilder& CameraBuilder::SetProjectionMode(
    ProjectionMode projection_mode) {
    projection_mode_ = projection_mode;
    return *this;
}
#pragma endregion CameraBuilder Inline Implementation
}  // namespace SoftRenderer
