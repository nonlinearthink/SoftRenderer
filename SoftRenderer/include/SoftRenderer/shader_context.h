#pragma once

#include <memory>

namespace SoftRenderer {
// The base class of the shader context, which use to store varring
// variables between the vertex and pixel shader.
template <typename DerivedContext>
class BaseShaderContext {
public:
    // Create a shader context that is a compile-time dynamic type.
    static std::unique_ptr<DerivedContext> Create() {
        return std::make_unique<DerivedContext>();
    }
};
}  // namespace SoftRenderer
