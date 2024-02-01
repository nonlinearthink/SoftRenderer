#pragma once

#include "SoftRenderer/color.h"
#include "SoftRenderer/vec.h"

namespace SoftRenderer {
struct Vertex {
    Vector3f position;
    Vector3f normal;
    Vector2f uv;
    Color color;
};
}  // namespace SoftRenderer
