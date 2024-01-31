#pragma once

#include <string>
#include <vector>

#include "SoftRenderer/transform.h"
#include "SoftRenderer/vec.h"

namespace SoftRenderer {
class Mesh {
public:
    friend class ObjLoader;

    Mesh() = default;
    explicit Mesh(std::string& name) : name_{name} {}

private:
    Transform transform_;
    std::string name_{"Untitled"};
    std::vector<std::shared_ptr<Vector3f>> vertices_;
    std::vector<std::shared_ptr<Vector3f>> normals_;
    std::vector<std::shared_ptr<Vector2f>> texure_coordinates_;
    std::vector<u32> vertex_indices_;
    std::vector<u32> normal_indices_;
    std::vector<u32> texture_indices_;
};
}  // namespace SoftRenderer
