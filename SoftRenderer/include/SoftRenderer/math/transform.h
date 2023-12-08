#include "SoftRenderer/math/matrix.h"
#include "SoftRenderer/math/vec.hpp"

namespace SoftRenderer {
class Transform {
public:
    Vector3f position;
    Vector3f rotation;
    Vector3f scaling;
    Matrix m;

    Transform():m() {}
    ~Transform() {}

    Transform& Translate(const Vector3f position);
    Transform& RotateX(const float angle);
    Transform& RotateY(const float angle);
    Transform& RotateZ(const float angle);
    Transform& Rotation(const Vector3f rotation);
    Transform& Scale(const Vector3f scaling);
};
}  // namespace SoftRenderer
