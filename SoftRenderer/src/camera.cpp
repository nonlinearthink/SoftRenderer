#include "SoftRenderer/camera.h"

using namespace SoftRenderer;

void Camera::ComputeViewMatrix() {}

void Camera::ComputeProjectionMatrix() {}

void Camera::Update() {
    if (!is_view_matrix_dirty_) {
        ComputeViewMatrix();
    }

    if (is_projection_matrix_dirty_) {
        ComputeProjectionMatrix();
    }
}
