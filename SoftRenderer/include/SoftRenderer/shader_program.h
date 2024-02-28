#pragma once

#include "SoftRenderer/color.h"
#include "SoftRenderer/shader_context.h"
#include "SoftRenderer/vertex.h"

namespace SoftRenderer {
// The shader program interface, Used to create a custom shader program.
class IShaderProgram {
public:
    virtual Vector3f VertexShader(const Vertex &vertex,
                                  ShaderContext &context) = 0;
    virtual Color PixelShader(const ShaderContext &context) = 0;
};
}  // namespace SoftRenderer
