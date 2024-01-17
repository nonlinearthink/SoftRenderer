#include "SoftRenderer/quaternion.h"

using namespace SoftRenderer;

Quaternion Quaternion::operator*(const Quaternion& q) const {
    return Quaternion(w * q.x + x * q.w + y * q.z - z * q.y,
                      w * q.y - x * q.z + y * q.w + z * q.x,
                      w * q.z + x * q.y - y * q.x + z * q.w,
                      w * q.w - x * q.x - y * q.y - z * q.z);
}

Quaternion Quaternion::Conjugate() const { return Quaternion(-x, -y, -z, w); }

float Quaternion::Norm() const {
    return std::sqrt(w * w + x * x + y * y + z * z);
}

Quaternion Quaternion::Normalize() const {
    float n = Norm();
    return Quaternion(x / n, y / n, z / n, w / n);
}
