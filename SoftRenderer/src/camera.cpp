#include "SoftRenderer/camera.h"

using namespace SoftRenderer;

void Camera::Update() {
    if (!is_view_matrix_ready_) {
        ComputeViewMatrix();
    }

    if (is_projection_matrix_ready_) {
        ComputeProjectionMatrix();
    }
}
