#pragma once

#include <memory>

#include "SoftRenderer/shader_context.h"
#include "SoftRenderer/vec.h"
#include "SoftRenderer/vertex.h"

namespace SoftRenderer {
// Define the shader program interface. Used to create a custom shader program.
//
// Template Parameters:
//     ContextType is the type of the shader context, which should be derived
//     from BaseShaderContext class.
template <typename ContextType>
class IShaderProgram {
public:
    // Create a shader context. Should be called and then pass to VertexShader
    // and PixelShader.
    static std::unique_ptr<ContextType> CreateContext() {
        return ContextType::Create();
    }

    virtual Vector3f VertexShader(const Vertex &vertex,
                                  ContextType &context) = 0;
    virtual Color PixelShader(const ContextType &context) = 0;
};

struct EmptyShaderContext : public BaseShaderContext<EmptyShaderContext> {};

class StandShaderProgram : public IShaderProgram<EmptyShaderContext> {
public:
    Vector3f VertexShader(const Vertex &vertex,
                          EmptyShaderContext &context) override;
    Color PixelShader(const EmptyShaderContext &context) override;
};
}  // namespace SoftRenderer
