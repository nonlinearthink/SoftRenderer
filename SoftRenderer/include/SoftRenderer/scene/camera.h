#include "SoftRenderer/math/quaternion.h"
#include "SoftRenderer/math/transform.h"
#include "SoftRenderer/math/vec.hpp"

namespace SoftRenderer {
class Camera {
public:
    Camera();
    ~Camera();

private:
    Vector3f position_;
    Vector3f rotation_;
    Transform transform_;
};
}  // namespace SoftRenderer