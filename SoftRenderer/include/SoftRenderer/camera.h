#pragma once

#include "SoftRenderer/matrix.h"
#include "SoftRenderer/transform.h"
#include "SoftRenderer/vec.h"

namespace SoftRenderer {
constexpr float DEFAULT_FOV = 30.f;
constexpr float DEFAULT_ASPECT = 16.f / 9.f;

// Camera Class
class Camera {
public:
    Camera(const Vector3f& position, const Vector3f& target, const Vector3f& up)
        : position_{position}, target_{target}, up_{up} {};

    inline void set_position(const Vector3f& position);
    inline void set_target(const Vector3f& target);
    inline void set_up(const Vector3f& up);
    inline void set_fov(float fov);
    inline void set_aspect(float aspect_);

    // Updates per frame to compute the view matrix and projection
    // matrix of this camera.
    void Update();

private:
    Vector3f position_;
    Vector3f target_;
    Vector3f up_;
    float fov_{DEFAULT_FOV};
    float aspect_{DEFAULT_ASPECT};
    Transform view_matrix_;
    bool is_view_matrix_ready_{false};
    Transform projection_matrix_;
    bool is_projection_matrix_ready_{false};

    void ComputeViewMatrix();
    void ComputeProjectionMatrix();
};

#pragma region Camera Inline Implementation

inline void Camera::set_position(const Vector3f& position) {
    position_.CopyFrom(position);
}

inline void Camera::set_target(const Vector3f& target) {
    target_.CopyFrom(target);
}

inline void Camera::set_up(const Vector3f& up) { up_.CopyFrom(up); }

inline void Camera::set_fov(float fov) { fov_ = fov; }

inline void Camera::set_aspect(float aspect) { aspect_ = aspect; }

#pragma endregion Camera Inline Implementation

class CameraBuilder {
public:
    inline CameraBuilder& SetPosition(const Vector3f& position);
    inline CameraBuilder& SetTarget(const Vector3f& target);
    inline CameraBuilder& SetUp(const Vector3f& up);
    inline CameraBuilder& SetFov(float fov);
    inline CameraBuilder& SetAspect(float aspect);
    inline std::unique_ptr<Camera> Build();

private:
    Vector3f position_;
    Vector3f target_;
    Vector3f up_;
    float fov_{DEFAULT_FOV};
    float aspect_{DEFAULT_ASPECT};
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

inline std::unique_ptr<Camera> CameraBuilder::Build() {
    auto camera = std::make_unique<Camera>(position_, target_, up_);
    camera->set_fov(fov_);
    camera->set_aspect(aspect_);

    return camera;
}

#pragma endregion CameraBuilder Inline Implementation
}  // namespace SoftRenderer
