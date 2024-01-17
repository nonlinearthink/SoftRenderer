#pragma once

#include <string>
#include <utility>
#include <vector>

#include "SoftRenderer/transform.h"
#include "SoftRenderer/vec.h"
#include "SoftRenderer/vertex.h"

namespace SoftRenderer {
class Mesh {
public:
    Mesh() = default;
    explicit Mesh(std::string name) : name_{std::move(name)} {}

    constexpr std::string& name_ref() { return name_; }
    constexpr std::vector<Vector3f>& vertices_ref() { return vertices_; }
    constexpr std::vector<Vector3f>& normal_ref() { return normal_; }
    constexpr std::vector<Vector2f>& uv_ref() { return uv_; }

private:
    Transform transform_;
    std::string name_;
    std::vector<Vector3f> vertices_;
    std::vector<Vector3f> normal_;
    std::vector<Vector2f> uv_;
    std::vector<u32> indices_;
};
}  // namespace SoftRenderer
