#pragma once

#include "SoftRenderer/math/vec.hpp"

namespace SoftRenderer {
struct Vertex {
    Vector3f position;
    Vector3f normal;
    Vector2f uv;
};
}  // namespace SoftRenderer
