#pragma once

#include <cassert>
#include <stdexcept>

#include "SoftRenderer/common.h"
#include "SoftRenderer/shader_context.h"

namespace SoftRenderer {
template <typename T>
class ShaderVariable {
public:
    ShaderVariable(u32 binding, ShaderContext& context)
        : binding_{binding}, context_{context} {}
    ShaderVariable(u32 binding, const ShaderContext& context)
        : binding_{binding}, context_{const_cast<ShaderContext&>(context)} {}
    DISABLE_COPY_AND_MOVE(ShaderVariable)

    void set(const T& value) noexcept {
        auto variable_table = context_.GetVariableTable<T>();
        variable_table.emplace(binding_, value);
    }

    T get() const {
        auto variable_table = context_.GetVariableTable<T>();
        auto it = variable_table.find(binding_);
        if (it == variable_table.end()) {
            throw std::runtime_error("Can't find the shader variable");
        } else {
            return it->second;
        }
    }

private:
    u32 binding_;
    ShaderContext& context_;
};
}  // namespace SoftRenderer
