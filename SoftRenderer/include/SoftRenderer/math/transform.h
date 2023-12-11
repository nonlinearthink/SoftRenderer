#include "SoftRenderer/math/matrix.hpp"
#include "SoftRenderer/math/vec.hpp"

namespace SoftRenderer {
class Transform {
public:
    Transform() : m_{} {}
    ~Transform() {}

    Matrix4 GetTransformMatrix() const;

    Transform& Translate(const Vector3f position);
    Transform& RotateX(const float angle);
    Transform& RotateY(const float angle);
    Transform& RotateZ(const float angle);
    Transform& Rotation(const Vector3f rotation);
    Transform& Scale(const Vector3f scaling);

private:
    Vector3f position_;
    Vector3f rotation_;
    Vector3f scaling_;
    Matrix4 m_;
};
}  // namespace SoftRenderer
