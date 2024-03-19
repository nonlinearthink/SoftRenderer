#pragma once

#include <map>

#include "SoftRenderer/color.h"
#include "SoftRenderer/common.h"
#include "SoftRenderer/vec.h"

namespace SoftRenderer {
// The shader context class, which use to store varring variables between the
// vertex and pixel shader.
class ShaderContext {
public:
    // Get the variable table based on the generic type, if failed it will cause
    // a compile time error.
    template <typename T>
    std::map<u32, T>& GetVariableTable();

private:
    std::map<u32, float> float_table_;
    std::map<u32, Color> color_table_;
    std::map<u32, Vector3f> vec3f_table_;
};

template <typename T>
std::map<u32, T>& ShaderContext::GetVariableTable() {
    if constexpr (std::is_same_v<T, float>) {
        return float_table_;
    } else if constexpr (std::is_same_v<T, Color>) {
        return color_table_;
    } else if constexpr (std::is_same_v<T, Vector3f>) {
        return vec3f_table_;
    } else {
        static_assert(std::is_same_v<T, void>,
                      "Unsupported type for ShaderVarriable");
    }
}
}  // namespace SoftRenderer
