#pragma once

#include "SoftRenderer/math/color.h"
#include "SoftRenderer/math/vec.hpp"

namespace SoftRenderer {
class Vertex {
public:
    Vector3f position;
    Vector3f normal;
    Color color;
    Vector2f uv;
};
}  // namespace SoftRenderer
