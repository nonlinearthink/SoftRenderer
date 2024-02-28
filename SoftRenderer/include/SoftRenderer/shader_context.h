#pragma once

#include <map>

#include "SoftRenderer/color.h"
#include "SoftRenderer/common.h"
#include "SoftRenderer/vec.h"

namespace SoftRenderer {
// The shader context class, which use to store varring variables between the
// vertex and pixel shader.
struct ShaderContext {
    std::map<u32, float> varring_float;
    std::map<u32, Color> varring_color;
    std::map<u32, Vector3f> varring_vec3f;
};
}  // namespace SoftRenderer
