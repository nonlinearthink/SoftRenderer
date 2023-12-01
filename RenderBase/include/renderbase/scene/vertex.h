#pragma once

#include "renderbase/math/color.h"
#include "renderbase/math/vec.hpp"

namespace RenderBase {
class Vertex {
public:
    Vector3f position;
    Vector3f normal;
    Color color;
    Vector2f uv;
};
}  // namespace RenderBase
