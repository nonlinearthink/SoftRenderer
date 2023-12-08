#include "SoftRenderer/math/quaternion.h"
#include "SoftRenderer/math/vec.hpp"

namespace SoftRenderer {
class Camera {
    Vector3f position;
    Vector3f rotation;

    Camera();
    ~Camera();
};
}  // namespace SoftRenderer