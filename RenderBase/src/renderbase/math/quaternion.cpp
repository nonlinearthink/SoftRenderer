#include "renderbase/math/quaternion.h"

using namespace RenderBase;

Quaternion Quaternion::operator*(const Quaternion& q) const {
    return Quaternion(w * q.x + x * q.w + y * q.z - z * q.y,
                      w * q.y - x * q.z + y * q.w + z * q.x,
                      w * q.z + x * q.y - y * q.x + z * q.w,
                      w * q.w - x * q.x - y * q.y - z * q.z);
}

Quaternion Quaternion::conjugate() const { return Quaternion(-x, -y, -z, w); }

float Quaternion::norm() const {
    return std::sqrt(w * w + x * x + y * y + z * z);
}

Quaternion Quaternion::normalize() const {
    float n = norm();
    return Quaternion(x / n, y / n, z / n, w / n);
}
