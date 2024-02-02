#include "SoftRenderer/camera.h"

#include <cmath>

#include "SoftRenderer/transform.h"

using namespace SoftRenderer;

void Camera::ComputeViewTransform() {
    if (!is_view_transform_dirty_) {
        view_transform_ =
            Transform::LookAt(position_, target_ - position_, up_);
    }
}

void Camera::ComputeProjectionTransform() {
    if (is_projection_transform_dirty_) {
        float bottom = -near_z_ * std::tan(fov_ / 2);
        float top = near_z_ * std::tan(fov_ / 2);
        float left = -top * aspect_;
        float right = top * aspect_;
        if (projection_mode_ == ProjectionMode::PERSPECTIVE) {
            projection_transform_ = Transform::Perspective(
                left, right, bottom, top, far_z_, near_z_);
        } else {
            projection_transform_ = Transform::Orthographic(
                left, right, bottom, top, far_z_, near_z_);
        }
    }
}

void Camera::Update() {
    ComputeViewTransform();
    ComputeProjectionTransform();
}

std::unique_ptr<Camera> CameraBuilder::Build() const {
    auto camera = std::make_unique<Camera>(position_, target_, up_);
    camera->set_fov(fov_);
    camera->set_aspect(aspect_);
    camera->set_near_z(near_z_);
    camera->set_far_z(far_z_);
    camera->set_projection_mode(projection_mode_);

    return camera;
}
